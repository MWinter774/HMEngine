#include "NeuralNetwork.h"
#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream> 
#include "Utilities.h"

bool HMEngine::Core::MachineLearning::NeuralNetwork::isSrand = false;

HMEngine::Core::MachineLearning::NeuralNetwork::NeuralNetwork(const std::vector<unsigned int>& topology, bool randomBias)
{
	unsigned int numLayers = topology.size();
	if (!isSrand)
	{
		srand(unsigned int(time(NULL)));
		HMEngine::Core::MachineLearning::NeuralNetwork::isSrand = true;
	}
	for (unsigned int layerNum = 0; layerNum < numLayers; layerNum++)
	{
		this->_layers.push_back(Layer());
		unsigned int numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		for (unsigned int neuronNum = 0; neuronNum <= topology[layerNum]; neuronNum++)
		{
			this->_layers.back().push_back(Neuron(numOutputs, neuronNum));
		}

		float biasValue = 1.0f;
		if (randomBias)
			biasValue = float(rand()) / RAND_MAX;
		this->_layers.back().back().SetOutputValue(biasValue);
	}
}

HMEngine::Core::MachineLearning::NeuralNetwork::NeuralNetwork(const std::vector<unsigned int>& topology, const NeuralNetwork& parent1,
	const NeuralNetwork& parent2, bool mutate) : NeuralNetwork(topology)
{
	if (!isSrand)
	{
		srand(unsigned int(time(NULL)));
		HMEngine::Core::MachineLearning::NeuralNetwork::isSrand = true;
	}
	std::vector<float> weights1;
	std::vector<float> weights2;
	std::vector<float> weights;
	this->GetWeightsOfNetwork(parent1, weights1);
	this->GetWeightsOfNetwork(parent2, weights2);
	auto k = rand();
	unsigned int crossoverPoint = k % (weights1.size() + 1);

	for (unsigned int i = 0; i < crossoverPoint; i++)
	{
		/* Mutates the weight */
		weights.push_back(weights1[i] + this->RandomGaussianNumber(0, 0.05f) * 2);
	}
	for (unsigned int i = crossoverPoint; i < weights2.size(); i++)
	{
		/* Mutates the weight */
		weights.push_back(weights2[i] + this->RandomGaussianNumber(0, 0.05f) * 2);
	}

	this->SetWeights(weights);
}

HMEngine::Core::MachineLearning::NeuralNetwork::NeuralNetwork(const std::string& nnFilePath)
{
	this->Load(nnFilePath);
}

HMEngine::Core::MachineLearning::NeuralNetwork::~NeuralNetwork()
{
}

void HMEngine::Core::MachineLearning::NeuralNetwork::SetWeights(const std::vector<float>& weights)
{
	unsigned int i = 0;

	for (auto& layer : this->_layers)
	{
		for (auto& neuron : layer)
		{
			for (auto& connection : neuron._outputWeights)
			{
				connection.weight = weights[i];
				i++;
			}
		}
	}
}

void HMEngine::Core::MachineLearning::NeuralNetwork::FeedForward(const std::vector<float>& input)
{
	assert(input.size() == this->_layers[0].size() - 1);

	for (unsigned int i = 0; i < input.size(); i++)
	{
		this->_layers[0][i].SetOutputValue(input[i]);
	}

	for (unsigned int layerNum = 1; layerNum < this->_layers.size(); layerNum++)
	{
		Layer& prevLayer = this->_layers[layerNum - 1];
		for (unsigned int n = 0; n < this->_layers[layerNum].size() - 1; n++)
		{
			this->_layers[layerNum][n].FeedForward(prevLayer);
		}
	}
}

void HMEngine::Core::MachineLearning::NeuralNetwork::BackProp(const std::vector<float>& target)
{
	Layer& outputLayer = this->_layers.back();
	this->_error = 0.0f;

	for (unsigned int n = 0; n < outputLayer.size() - 1; n++)
	{
		float delta = target[n] - outputLayer[n].GetOutputValue();
		this->_error += delta * delta;
	}
	this->_error /= outputLayer.size() - 1;
	this->_error = sqrt(this->_error);

	this->_recentAverageError = (this->_recentAverageError * this->_recentAverageSmoothingFactor + this->_error) / (this->_recentAverageSmoothingFactor + 1.0f);

	for (unsigned int n = 0; n < outputLayer.size() - 1; n++)
	{
		outputLayer[n].CalcOutputGradients(target[n]);
	}

	for (unsigned int layerNum = this->_layers.size() - 2; layerNum > 0; layerNum--)
	{
		Layer& hiddenLayer = this->_layers[layerNum];
		Layer& nextLayer = this->_layers[layerNum + 1];

		for (unsigned int n = 0; n < hiddenLayer.size(); n++)
		{
			hiddenLayer[n].CalcHiddenGradients(nextLayer);
		}
	}

	for (unsigned int layerNum = this->_layers.size() - 1; layerNum > 0; layerNum--)
	{
		Layer& layer = this->_layers[layerNum];
		Layer& prevLayer = this->_layers[layerNum - 1];

		for (unsigned int n = 0; n < layer.size() - 1; n++)
		{
			layer[n].UpdateInputWeights(prevLayer);
		}
	}
}

std::vector<float> HMEngine::Core::MachineLearning::NeuralNetwork::GetResults() const
{
	std::vector<float> results;

	for (unsigned int n = 0; n < this->_layers.back().size() - 1; n++)
	{
		results.push_back(this->_layers.back()[n].GetOutputValue());
	}

	return results;
}

void HMEngine::Core::MachineLearning::NeuralNetwork::Save(const std::string& fileName)
{
	std::vector<float> myWeights;
	this->GetWeightsOfNetwork(*this, myWeights);

	std::ofstream neuralNetworkFile(fileName);
	if (!neuralNetworkFile.is_open())
		HMEngine::Core::Utilities::ThrowException("UNABLE TO OPEN FILE: " + fileName + "!!");

	for (auto& weight : myWeights)
	{
		neuralNetworkFile << weight << std::endl;
	}

	neuralNetworkFile.close();
}

void HMEngine::Core::MachineLearning::NeuralNetwork::Load(const std::string& fileName)
{
	std::vector<float> myWeights;
	std::ifstream neuralNetworkFile(fileName);
	if (!neuralNetworkFile.is_open())
		HMEngine::Core::Utilities::ThrowException("UNABLE TO OPEN FILE: " + fileName + "!!");
	std::string line;

	while (std::getline(neuralNetworkFile, line))
	{
		myWeights.push_back(std::stof(line));
	}

	this->SetWeights(myWeights);
}

void HMEngine::Core::MachineLearning::NeuralNetwork::GetWeightsOfNetwork(const NeuralNetwork& neuralNetwork, std::vector<float>& weights)
{
	for (auto& layer : neuralNetwork._layers)
	{
		for (auto& neuron : layer)
		{
			for (auto& weight : neuron._outputWeights)
			{
				weights.push_back(weight.weight);
			}
		}
	}
}

float HMEngine::Core::MachineLearning::NeuralNetwork::RandomGaussianNumber(float mean, float standardDeviation)
{
	static float n2 = 0.0f;
	static bool n2_cached = false;
	if (!n2_cached)
	{
		float x, y, r;
		do
		{
			x = 2.0f * rand() / RAND_MAX - 1;
			y = 2.0f * rand() / RAND_MAX - 1;

			r = x * x + y * y;
		} while (r == 0.0f || r > 1.0f);
		{
			float d = sqrt(-2.0f * log(r) / r);
			float n1 = x * d;
			n2 = y * d;
			float result = n1 * standardDeviation + mean;
			n2_cached = true;
			return result;
		}
	}
	else
	{
		n2_cached = false;
		return n2 * standardDeviation + mean;
	}
}
