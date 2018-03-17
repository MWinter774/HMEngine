#pragma once
#include <vector>
#include "Neuron.h"

namespace HMEngine
{
	namespace Core
	{
		namespace MachineLearning
		{
			class NeuralNetwork
			{
				typedef std::vector<Neuron> Layer;
			public:
				NeuralNetwork(const std::vector<unsigned int>& topology);
				~NeuralNetwork();

				void FeedForward(const std::vector<float>& input);
				void BackProp(const std::vector<float>& target);
				std::vector<float> GetResults() const;

			private:
				std::vector<Layer> _layers;
				float _error;
				float _recentAverageError;
				float _recentAverageSmoothingFactor;
			};
		}
	}
}