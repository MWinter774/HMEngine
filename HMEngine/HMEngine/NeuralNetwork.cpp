#include "NeuralNetwork.h"
#include <cassert>
#include <ctime>

HMEngine::Core::MachineLearning::NeuralNetwork::NeuralNetwork(const std::vector<unsigned int>& topology)
{
	unsigned int numLayers = topology.size();
	srand(unsigned int(time(NULL)));

	for (unsigned int layerNum = 0; layerNum < numLayers; layerNum++)
	{
		this->_layers.push_back(Layer());
		unsigned int numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		for (unsigned int neuronNum = 0; neuronNum <= topology[layerNum]; neuronNum++)
		{
			this->_layers.back().push_back(Neuron(numOutputs, neuronNum));
		}

		this->_layers.back().back().SetOutputValue(1.0f);
	}
}


HMEngine::Core::MachineLearning::NeuralNetwork::~NeuralNetwork()
{
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