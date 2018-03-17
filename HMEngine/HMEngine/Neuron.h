#pragma once
#include <vector>

namespace HMEngine
{
	namespace Core
	{
		namespace MachineLearning
		{
			class Neuron
			{
				typedef std::vector<Neuron> Layer;
				typedef struct Connection
				{
					double weight;
					double deltaWeight;
				} Connection;
			public:
				Neuron(unsigned numOutputs, unsigned myIndex);
				void SetOutputValue(double val) { this->_outputVal = val; }
				double GetOutputValue(void) const { return this->_outputVal; }
				void FeedForward(const Layer& prevLayer);
				void CalculateOutputGradients(double targetVals);
				void CalculateHiddenGradients(const Layer& nextLayer);
				void UpdateInputWeights(Layer& prevLayer);
			private:
				static const double ETA;
				static const double ALPHA;
				static double TransferFunction(double x);
				static double TransferFunctionDerivative(double x);

				static double RandomWeight(void) { return rand() / double(RAND_MAX); }
				double SumDOW(const Layer& nextLayer) const;

				double _outputVal;
				std::vector<Connection> _outputWeights;
				unsigned _myIndex;
				double _gradient;
			};
		}
	}
}