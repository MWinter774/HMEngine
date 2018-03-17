#include "NeuralNetwork.h"
#include <iostream>
#include <assert.h>
#include <time.h>

const double HMEngine::Core::MachineLearning::NeuralNetwork::RECENT_AVERAGE_SMOOTHING_FACTOR = 100.0; // Number of training samples to average over

std::vector<double> HMEngine::Core::MachineLearning::NeuralNetwork::GetResults() const
{
	std::vector<double> resultVals;

	for (unsigned int n = 0; n < this->_layers.back().size() - 1; ++n)
	{
		resultVals.push_back(this->_layers.back()[n].GetOutputValue());
	}

	return resultVals;
}

void HMEngine::Core::MachineLearning::NeuralNetwork::BackProp(const std::vector<double>& targetVals)
{
	// Calculate overal net error (RMS of output neuron errors)

	Layer &outputLayer = this->_layers.back();
	this->_error = 0.0;

	for (unsigned int n = 0; n < outputLayer.size() - 1; ++n)
	{
		double delta = targetVals[n] - outputLayer[n].GetOutputValue();
		this->_error += delta * delta;
	}
	this->_error /= outputLayer.size() - 1; // get average error squared
	this->_error = sqrt(this->_error); // RMS

							 // Implement a recent average measurement:

	this->_recentAverageError =
		(this->_recentAverageError * HMEngine::Core::MachineLearning::NeuralNetwork::RECENT_AVERAGE_SMOOTHING_FACTOR + this->_error)
		/ (HMEngine::Core::MachineLearning::NeuralNetwork::RECENT_AVERAGE_SMOOTHING_FACTOR + 1.0);
	// Calculate output layer gradients

	for (unsigned int n = 0; n < outputLayer.size() - 1; ++n)
	{
		outputLayer[n].CalculateOutputGradients(targetVals[n]);
	}
	// Calculate gradients on hidden layers

	for (unsigned int layerNum = this->_layers.size() - 2; layerNum > 0; --layerNum)
	{
		Layer &hiddenLayer = this->_layers[layerNum];
		Layer &nextLayer = this->_layers[layerNum + 1];

		for (unsigned int n = 0; n < hiddenLayer.size(); ++n)
		{
			hiddenLayer[n].CalculateHiddenGradients(nextLayer);
		}
	}

	// For all layers from outputs to first hidden layer,
	// update connection weights

	for (unsigned int layerNum = this->_layers.size() - 1; layerNum > 0; --layerNum)
	{
		Layer &layer = this->_layers[layerNum];
		Layer &prevLayer = this->_layers[layerNum - 1];

		for (unsigned int n = 0; n < layer.size() - 1; ++n)
		{
			layer[n].UpdateInputWeights(prevLayer);
		}
	}
}

void HMEngine::Core::MachineLearning::NeuralNetwork::FeedForward(const std::vector<double>& inputVals)
{
	// Check the num of inputVals euqal to neuronnum expect bias
	assert(inputVals.size() == this->_layers[0].size() - 1);

	// Assign {latch} the input values into the input neurons
	for (unsigned int i = 0; i < inputVals.size(); ++i) {
		this->_layers[0][i].SetOutputValue(inputVals[i]);
	}

	// Forward propagate
	for (unsigned int layerNum = 1; layerNum < this->_layers.size(); ++layerNum) {
		Layer &prevLayer = this->_layers[layerNum - 1];
		for (unsigned int n = 0; n < this->_layers[layerNum].size() - 1; ++n) {
			this->_layers[layerNum][n].FeedForward(prevLayer);
		}
	}
}

HMEngine::Core::MachineLearning::NeuralNetwork::NeuralNetwork(const std::vector<unsigned int>& topology)
{
	srand(unsigned int(time(NULL)));

	unsigned int numLayers = topology.size();
	for (unsigned int layerNum = 0; layerNum < numLayers; ++layerNum)
	{
		this->_layers.push_back(Layer());
		// numOutputs of layer[i] is the numInputs of layer[i+1]
		// numOutputs of last layer is 0
		unsigned int numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		// We have made a new Layer, now fill it ith neurons, and
		// add a bias neuron to the layer:
		for (unsigned int neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
		{
			this->_layers.back().push_back(Neuron(numOutputs, neuronNum));
		}

		// Force the bias node's output value to 1.0. It's the last neuron created above
		this->_layers.back().back().SetOutputValue(1.0);
	}
}