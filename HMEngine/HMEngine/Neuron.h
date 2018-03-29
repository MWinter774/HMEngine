#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

namespace HMEngine
{
	namespace Core
	{
		namespace MachineLearning
		{
			class NeuralNetwork;
			class Neuron
			{
				typedef std::vector<Neuron> Layer;
				typedef struct
				{
					float weight;
					float deltaWeight;
				} Connection;
				friend class NeuralNetwork;
			public:
				Neuron(unsigned int numOutputs, unsigned int index);
				~Neuron();

				inline void SetOutputValue(float val) { this->_outputVal = val; }
				inline float GetOutputValue() const { return this->_outputVal; }

				void FeedForward(const Layer& prevLayer);

				void CalcOutputGradients(float targetVal);
				void CalcHiddenGradients(const Layer& nextLayer);
				void UpdateInputWeights(Layer& prevLayer);

			private:
				inline static float RandomWeight()
				{
					return rand() / float(RAND_MAX);
				}
				inline static float SigmoidFunction(float x)
				{
					return 1 / (1 + exp(-x));
				}
				inline static float SigmoidFunctionDerivative(float x)
				{
					return exp(x) / ((1 + exp(x)) * (1 + exp(x)));
				}
				inline static float TanhFunction(float x)
				{
					return tanh(x);
				}
				inline static float TanhFunctionDerivative(float x)
				{
					return 1 - x * x;
				}
				inline static float ReLuFunction(float x)
				{
					return std::fmax(0.0f, x);
				}
				inline static float ReLuFunctionDerivative(float x)
				{
					if (x > 0)
						return 1;
					return 0;
				}
				static float ETA;
				static float ALPHA;

				float _outputVal;
				std::vector<Connection> _outputWeights;
				unsigned int _myIndex;
				float _gradient;

				float SumDOW(const Layer& nextLayer) const;
			};
		}
	}
}