#pragma once
#include <vector>
#include "Neuron.h"

namespace HMEngine
{
	namespace Core
	{
		namespace MachineLearning
		{
				typedef std::vector<HMEngine::Core::MachineLearning::Neuron> Layer;
			class NeuralNetwork
			{
				
			public:
				NeuralNetwork(const std::vector<unsigned int>& topology);
				void FeedForward(const std::vector<double>& inputVals);
				void BackProp(const std::vector<double>& targetVals);
				std::vector<double> GetResults() const;
				inline double GetRecentAverageError() const { return this->_recentAverageError; }

			private:
				std::vector<Layer> _layers; //m_layers[layerNum][neuronNum]
				double _error;
				double _recentAverageError;
				static const double RECENT_AVERAGE_SMOOTHING_FACTOR;
			};
		}
	}
}