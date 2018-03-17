#include "Neuron.h"

const double HMEngine::Core::MachineLearning::Neuron::ETA = 0.15; // overall net learning rate
const double HMEngine::Core::MachineLearning::Neuron::ALPHA = 0.5; // momentum, multiplier of last deltaWeight, [0.0..n]

void HMEngine::Core::MachineLearning::Neuron::UpdateInputWeights(Layer& prevLayer)
{
	// The weights to be updated are in the Connection container
	// in the nuerons in the preceding layer

	for (unsigned n = 0; n < prevLayer.size(); ++n)
	{
		Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron._outputWeights[this->_myIndex].deltaWeight;

		double newDeltaWeight =
			// Individual input, magnified by the gradient and train rate:
			HMEngine::Core::MachineLearning::Neuron::ETA
			* neuron.GetOutputValue()
			* this->_gradient
			// Also add momentum = a fraction of the previous delta weight
			+ HMEngine::Core::MachineLearning::Neuron::ALPHA
			* oldDeltaWeight;
		neuron._outputWeights[this->_myIndex].deltaWeight = newDeltaWeight;
		neuron._outputWeights[this->_myIndex].weight += newDeltaWeight;
	}
}
double HMEngine::Core::MachineLearning::Neuron::SumDOW(const Layer& nextLayer) const
{
	double sum = 0.0;

	// Sum our contributions of the errors at the nodes we feed

	for (unsigned n = 0; n < nextLayer.size() - 1; ++n)
	{
		sum += this->_outputWeights[n].weight * nextLayer[n]._gradient;
	}

	return sum;
}

void HMEngine::Core::MachineLearning::Neuron::CalculateHiddenGradients(const Layer& nextLayer)
{
	double dow = this->SumDOW(nextLayer);
	this->_gradient = dow * HMEngine::Core::MachineLearning::Neuron::TransferFunctionDerivative(this->_outputVal);
}
void HMEngine::Core::MachineLearning::Neuron::CalculateOutputGradients(double targetVals)
{
	double delta = targetVals - this->_outputVal;
	this->_gradient = delta * HMEngine::Core::MachineLearning::Neuron::TransferFunctionDerivative(this->_outputVal);
}

double HMEngine::Core::MachineLearning::Neuron::TransferFunction(double x)
{
	// tanh - output range [-1.0..1.0]
	return tanh(x);
}

double HMEngine::Core::MachineLearning::Neuron::TransferFunctionDerivative(double x)
{
	// tanh derivative
	return 1.0 - x * x;
}

void HMEngine::Core::MachineLearning::Neuron::FeedForward(const Layer& prevLayer)
{
	double sum = 0.0;

	// Sum the previous layer's outputs (which are our inputs)
	// Include the bias node from the previous layer.

	for (unsigned n = 0; n < prevLayer.size(); ++n)
	{
		sum += prevLayer[n].GetOutputValue() *
			prevLayer[n]._outputWeights[this->_myIndex].weight;
	}

	this->_outputVal = HMEngine::Core::MachineLearning::Neuron::TransferFunction(sum);
}

HMEngine::Core::MachineLearning::Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
	for (unsigned c = 0; c < numOutputs; ++c)
	{
		this->_outputWeights.push_back(Connection());
		this->_outputWeights.back().weight = this->RandomWeight();
	}

	this->_myIndex = myIndex;
}