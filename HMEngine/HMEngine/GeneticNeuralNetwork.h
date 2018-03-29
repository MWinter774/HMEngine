#pragma once
#include "NeuralNetwork.h"
#include <map>
#include <functional>
#include <string>

namespace HMEngine
{
	namespace Core
	{
		namespace MachineLearning
		{
			class GeneticNeuralNetwork
			{
				typedef std::function<bool(const std::pair<HMEngine::Core::MachineLearning::NeuralNetwork*, float>&,
					const std::pair<HMEngine::Core::MachineLearning::NeuralNetwork*, float>&)> Comparator;
				typedef std::pair<HMEngine::Core::MachineLearning::NeuralNetwork*, float> GeneticNeuralNetworkData;
			public:
				GeneticNeuralNetwork(unsigned int populationSize, const std::vector<unsigned int>& topology);
				GeneticNeuralNetwork(const std::string& gnnFilePath);
				~GeneticNeuralNetwork();

				void FeedForward(const std::vector<float>& input);
				std::vector<float> GetResults();
				void SetFitness(float fitness);
				void Step();
				std::vector<GeneticNeuralNetworkData> Selection();
				std::vector<GeneticNeuralNetworkData> Breed(unsigned int amount, const std::vector<GeneticNeuralNetworkData>& parents);
				void Terminate(const std::vector<GeneticNeuralNetworkData>& except);

				void Save(const std::string& fileName);
				void Load(const std::string& fileName);

			private:
				static std::vector<std::string> SplitString(const std::string& string, char delimiter);

				//std::map<HMEngine::Core::MachineLearning::NeuralNetwork*, float> _population;
				std::vector<GeneticNeuralNetworkData> _population;
				HMEngine::Core::MachineLearning::NeuralNetwork* _currentActiveNetwork;
				std::vector<GeneticNeuralNetworkData>::iterator _it;
				float _truncation;
				unsigned int _populationSize;
				std::vector<unsigned int> _topology;
				unsigned int _generationNumber;

				void ResetFitnesses();
			};
		}
	}
}