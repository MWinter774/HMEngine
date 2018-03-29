#pragma once
#include <vector>
#include "Neuron.h"
#include <string>

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
				static void GetWeightsOfNetwork(const NeuralNetwork& neuralNetwork, std::vector<float>& weights);

				NeuralNetwork(const std::vector<unsigned int>& topology, bool randomBias = false);
				NeuralNetwork(const std::vector<unsigned int>& topology, const NeuralNetwork& parent1, const NeuralNetwork& parent2, bool mutate = false);
				NeuralNetwork(const std::string& nnFilePath);
				~NeuralNetwork();

				void SetWeights(const std::vector<float>& weights);
				void FeedForward(const std::vector<float>& input);
				void BackProp(const std::vector<float>& target);
				std::vector<float> GetResults() const;
				void Save(const std::string& fileName);
				void Load(const std::string& fileName);

			private:
				static float RandomGaussianNumber(float mean, float standardDeviation);
				static bool isSrand;

				std::vector<Layer> _layers;
				float _error;
				float _recentAverageError;
				float _recentAverageSmoothingFactor;
			};
		}
	}
}