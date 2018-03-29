#pragma once
#include "Component.h"
#include "NeuralNetwork.h"
#include "GeneticNeuralNetwork.h"
#include "PhysicalCameraController.h"
#include "PhysicalPlayer.h"

class EnemyBot;
namespace HMEngine
{
	namespace Components
	{
		class BrainComponent : public HMEngine::Components::Component
		{
		public:
			BrainComponent(const HMEngine::PhysicalPlayer& player);
			BrainComponent(const HMEngine::PhysicalPlayer& player, const std::string& gnnFilePath);
			~BrainComponent();
			BrainComponent(const HMEngine::Components::BrainComponent& other);
			HMEngine::Components::BrainComponent& operator=(const HMEngine::Components::BrainComponent& other);

			inline HMEngine::Components::Component* Clone() override { return new HMEngine::Components::BrainComponent(*this); }

			void UpdateEvent() override;

			void AttachToGameObjectEvent() override;

			void Lost();

		private:
			HMEngine::Core::MachineLearning::GeneticNeuralNetwork _gnn;
			const HMEngine::PhysicalPlayer* _player;
			const HMEngine::PhysicalPlayer::MovementData* _playerMovement;
			std::vector<float> _currentPlayerMovement;
			std::vector<float> _futurePlayerMovement;
			EnemyBot* _parent;
			std::string _gnnFilePath;
			float _timer;
			float _rightAVG; //temp
			float _leftAVG; //temp
			float _forwardAVG; //temp
			float _backwardAVG; //temp
			int _count; //temp

			inline void ResetCurrentPlayerMovement()
			{
				_currentPlayerMovement[0] = 0.0;
				_currentPlayerMovement[1] = 0.0;
				_currentPlayerMovement[2] = 0.0;
				_currentPlayerMovement[3] = 0.0;
			}
			inline void ConstructCurrentPlayerMovement()
			{
				this->ResetCurrentPlayerMovement();
				if (this->_playerMovement->forward)
				{
					_currentPlayerMovement[0] = 1.0;
				}
				if (this->_playerMovement->backward)
				{
					_currentPlayerMovement[1] = 1.0;
				}
				if (this->_playerMovement->right)
				{
					_currentPlayerMovement[2] = 1.0;
				}
				if (this->_playerMovement->left)
				{
					_currentPlayerMovement[3] = 1.0;
				}
			}

			void FeedForward();
		};
	}
}