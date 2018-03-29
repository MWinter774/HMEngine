#include "GeneticNeuralNetwork.h"
#include <cassert>
#include <algorithm>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Utilities.h"

HMEngine::Core::MachineLearning::GeneticNeuralNetwork::GeneticNeuralNetwork(unsigned int populationSize, const std::vector<unsigned int>& topology) :
	_population(), _truncation(0.5f), _populationSize(populationSize), _topology(topology), _generationNumber(1)
{
	assert(populationSize > 0);
	for (unsigned int i = 0; i < populationSize; i++)
	{
		this->_population.push_back(GeneticNeuralNetworkData(new HMEngine::Core::MachineLearning::NeuralNetwork(topology, true), 0.0f));
	}
	this->_currentActiveNetwork = (*this->_population.begin()).first;
	this->_it = this->_population.begin();

	std::cout << "Generation #" << this->_generationNumber << std::endl;
	this->_generationNumber++;
}

HMEngine::Core::MachineLearning::GeneticNeuralNetwork::GeneticNeuralNetwork(const std::string& gnnFilePath) : _truncation(0.5f), _generationNumber(1)
{
	this->Load(gnnFilePath);
	this->_it = this->_population.begin();
	this->_currentActiveNetwork = (*this->_it).first;

	std::cout << "Generation #" << this->_generationNumber << std::endl;
	this->_generationNumber++;
}

HMEngine::Core::MachineLearning::GeneticNeuralNetwork::~GeneticNeuralNetwork()
{
	for (auto& pair : this->_population)
		delete pair.first;
}

void HMEngine::Core::MachineLearning::GeneticNeuralNetwork::FeedForward(const std::vector<float>& input)
{
	this->_currentActiveNetwork->FeedForward(input);
}

std::vector<float> HMEngine::Core::MachineLearning::GeneticNeuralNetwork::GetResults()
{
	return this->_currentActiveNetwork->GetResults();
}

void HMEngine::Core::MachineLearning::GeneticNeuralNetwork::SetFitness(float fitness)
{
	(*this->_it).second = fitness;
}

void HMEngine::Core::MachineLearning::GeneticNeuralNetwork::Step()
{
	this->_it++;
	if (this->_it == this->_population.end())
	{
		std::cout << "Generation #" << this->_generationNumber << std::endl;
		auto selected = this->Selection();
		this->Terminate(selected);
		auto offsprings = this->Breed(this->_populationSize - this->_population.size(), selected);
		for (auto& offspring : offsprings)
			this->_population.push_back(offspring);

		this->_it = this->_population.begin();
		this->_currentActiveNetwork = (*this->_it).first;
		this->ResetFitnesses();
		this->_generationNumber++;
	}
	else
	{
		this->_currentActiveNetwork = (*this->_it).first;
	}
}

std::vector<HMEngine::Core::MachineLearning::GeneticNeuralNetwork::GeneticNeuralNetworkData> HMEngine::Core::MachineLearning::GeneticNeuralNetwork::Selection()
{
	/* Sorts the vector */
	HMEngine::Core::MachineLearning::GeneticNeuralNetwork::Comparator compFunctor = [](const std::pair<HMEngine::Core::MachineLearning::NeuralNetwork*, float>& elem1,
		const std::pair<HMEngine::Core::MachineLearning::NeuralNetwork*, float>& elem2)
	{
		return elem1.second > elem2.second;
	};
	std::sort(this->_population.begin(), this->_population.end(), compFunctor);

	std::vector<HMEngine::Core::MachineLearning::GeneticNeuralNetwork::GeneticNeuralNetworkData> selected;
	for (unsigned int i = 0; i < this->_population.size() * this->_truncation; i++)
	{
		selected.push_back(this->_population[i]);
	}

	return selected;
}

std::vector<HMEngine::Core::MachineLearning::GeneticNeuralNetwork::GeneticNeuralNetworkData>
HMEngine::Core::MachineLearning::GeneticNeuralNetwork::Breed(unsigned int amount, const std::vector<GeneticNeuralNetworkData>& parents)
{
	assert(parents.size() * (parents.size() - 1) / 2 >= amount);
	std::vector<GeneticNeuralNetworkData> childs;

	while (childs.size() < amount)
	{
		for (auto& parent1 : parents)
		{
			for (auto& parent2 : parents)
			{
				if (parent1.first != parent2.first && childs.size() < amount)
				{
					NeuralNetwork* child = new NeuralNetwork(this->_topology, *parent1.first, *parent2.first, true);
					childs.push_back(GeneticNeuralNetworkData(child, 0.0f));
				}
			}
		}
	}

	return childs;
}

void HMEngine::Core::MachineLearning::GeneticNeuralNetwork::Terminate(const std::vector<GeneticNeuralNetworkData>& except)
{
	bool canDelete = true;
	for (auto& pair : this->_population)
	{
		canDelete = true;
		for (auto& toKeep : except)
		{
			if (pair.first == toKeep.first)
			{
				canDelete = false;
			}
		}
		if (canDelete)
			delete pair.first;
	}
	this->_population.clear();
	for (auto& toKeep : except)
	{
		this->_population.push_back(toKeep);
	}
}

void HMEngine::Core::MachineLearning::GeneticNeuralNetwork::Save(const std::string& fileName)
{
	std::ofstream neuralNetworkFile(fileName);
	if (!neuralNetworkFile.is_open())
		HMEngine::Core::Utilities::ThrowException("UNABLE TO OPEN FILE: " + fileName + "!!");

	/* Writes the topolgy */
	neuralNetworkFile << "Topology:" << "{";
	int index = 0;
	for (auto& t : this->_topology)
	{
		if (index != this->_topology.size() - 1)
			neuralNetworkFile << t << ",";
		else
			neuralNetworkFile << t;
		index++;
	}
	neuralNetworkFile << "}" << std::endl;

	/* Writes the population */
	neuralNetworkFile << "Population:" << std::endl << "{" << std::endl;
	index = 0;
	for (auto& pair : this->_population)
	{
		std::vector<float> nnWeights;
		HMEngine::Core::MachineLearning::NeuralNetwork::GetWeightsOfNetwork(*pair.first, nnWeights);
		for (auto& weight : nnWeights)
		{
			neuralNetworkFile << weight << std::endl;
		}
		if (index != this->_population.size() - 1)
			neuralNetworkFile << "}" << std::endl << "{" << std::endl;
		else
			neuralNetworkFile << "}";
		index++;
	}

	neuralNetworkFile.close();
}

void HMEngine::Core::MachineLearning::GeneticNeuralNetwork::Load(const std::string& fileName)
{
	std::ifstream neuralNetworkFile(fileName);
	if (!neuralNetworkFile.is_open())
	{	
		//HMEngine::Core::Utilities::ThrowException("UNABLE TO OPEN FILE: " + fileName + "!!");
		this->Save(fileName); //temp!
		return; //temp!
	}
	std::string line;

	this->_topology.clear();
	for (auto& pair : this->_population)
		delete pair.first;
	this->_population.clear();

	/* Reads topology */
	std::getline(neuralNetworkFile, line); //Reads the Topology line
	auto splittedLine = HMEngine::Core::MachineLearning::GeneticNeuralNetwork::SplitString(line, ':');
	std::string topologyDict = splittedLine[1];
	topologyDict.erase(topologyDict.begin());
	topologyDict.erase(topologyDict.end() - 1);
	auto topology = HMEngine::Core::MachineLearning::GeneticNeuralNetwork::SplitString(topologyDict, ',');
	for (auto& i : topology)
		this->_topology.push_back(std::stoi(i));

	std::getline(neuralNetworkFile, line); //Reads the Population line

	std::vector<float> nnWeights;
	HMEngine::Core::MachineLearning::NeuralNetwork* currNN = nullptr;
	while (std::getline(neuralNetworkFile, line))
	{
		if (line.find("{") != std::string::npos) //if current line is start of a neural network
		{
			currNN = new HMEngine::Core::MachineLearning::NeuralNetwork(this->_topology);
		}
		else if (line.find("}") != std::string::npos) //if current line is end of a neural network
		{
			currNN->SetWeights(nnWeights);
			this->_population.push_back(GeneticNeuralNetworkData(currNN, 0.0f));
			nnWeights.clear();
		}
		else
		{
			nnWeights.push_back(std::stof(line));
		}
	}

	this->_populationSize = this->_population.size();
	neuralNetworkFile.close();
}

std::vector<std::string> HMEngine::Core::MachineLearning::GeneticNeuralNetwork::SplitString(const std::string& string, char delimiter)
{
	std::vector<std::string> strings = std::vector<std::string>();
	std::string currWord;
	std::istringstream stringStream(string);

	while (std::getline(stringStream, currWord, delimiter))
	{
		if (!currWord.empty())
			strings.push_back(currWord);
	}

	return strings;
}

void HMEngine::Core::MachineLearning::GeneticNeuralNetwork::ResetFitnesses()
{
	for (auto& pair : this->_population)
	{
		pair.second = 0.0f;
	}
}
