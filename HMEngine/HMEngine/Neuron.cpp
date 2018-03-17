#include "Neuron.h"

float HMEngine::Core::MachineLearning::Neuron::ETA = 0.15f;
float HMEngine::Core::MachineLearning::Neuron::ALPHA = 0.5f;

HMEngine::Core::MachineLearning::Neuron::Neuron(unsigned int numOutputs, unsigned int index) : _myIndex(index), _outputVal(0)
{
	for (unsigned int c = 0; c < numOutputs; c++)
	{
		Connection connection = Connection();
		connection.weight = this->RandomWeight();
		this->_outputWeights.push_back(connection);
	}
}

HMEngine::Core::MachineLearning::Neuron::~Neuron()
{
}

void HMEngine::Core::MachineLearning::Neuron::FeedForward(const Layer& prevLayer)
{
	float sum = 0.0f;

	for (unsigned int n = 0; n < prevLayer.size(); n++)
	{
		sum += prevLayer[n].GetOutputValue() * prevLayer[n]._outputWeights[this->_myIndex].weight;
	}

	this->_outputVal = Neuron::TransferFunction(sum);
}

void HMEngine::Core::MachineLearning::Neuron::CalcOutputGradients(float targetVal)
{
	float delta = targetVal - this->_outputVal;
	this->_gradient = delta * Neuron::TransferFunctionDerivative(this->_outputVal);
}

void HMEngine::Core::MachineLearning::Neuron::CalcHiddenGradients(const Layer& nextLayer)
{
	float dow = this->SumDOW(nextLayer);
	this->_gradient = dow * Neuron::TransferFunctionDerivative(this->_outputVal);
}

void HMEngine::Core::MachineLearning::Neuron::UpdateInputWeights(Layer& prevLayer)
{
	for (unsigned int n = 0; n < prevLayer.size(); n++)
	{
		Neuron& neuron = prevLayer[n];
		float oldDeltaWeight = neuron._outputWeights[this->_myIndex].deltaWeight;

		float newDeltaWeight = Neuron::ETA * neuron.GetOutputValue()*this->_gradient + Neuron::ALPHA * oldDeltaWeight;

		neuron._outputWeights[this->_myIndex].deltaWeight = newDeltaWeight;
		neuron._outputWeights[this->_myIndex].weight += newDeltaWeight;
	}
}

float HMEngine::Core::MachineLearning::Neuron::SumDOW(const Layer& nextLayer) const
{
	float sum = 0.0f;

	for (unsigned int n = 0; n < nextLayer.size() - 1; n++)
	{
		sum += this->_outputWeights[n].weight * nextLayer[n]._gradient;
	}

	return sum;
}
