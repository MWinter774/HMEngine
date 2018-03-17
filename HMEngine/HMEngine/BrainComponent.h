#pragma once
#include "Component.h"
#include "NeuralNetwork.h"
#include "CameraController.h"

namespace HMEngine
{
	class Player;

	namespace Components
	{
		class BrainComponent : public HMEngine::Components::Component
		{
		public:
			BrainComponent(const HMEngine::Player& player);
			~BrainComponent();
			BrainComponent(const HMEngine::Components::BrainComponent& other);
			HMEngine::Components::BrainComponent& operator=(const HMEngine::Components::BrainComponent& other);

			inline HMEngine::Components::Component* Clone() override { return new HMEngine::Components::BrainComponent(*this); }

			void UpdateEvent() override;

		private:
			HMEngine::Core::MachineLearning::NeuralNetwork _neuralNetwork;
			const HMEngine::Player* _player;
			const HMEngine::Components::MovementData* _playerMovement;
			std::vector<float> _currentPlayerMovement;
			std::vector<float> _futurePlayerMovement;

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
					//std::cout << "Player is going forward" << std::endl;
					_currentPlayerMovement[0] = 1.0;
				}
				if (this->_playerMovement->backward)
				{
					//std::cout << "Player is going backward" << std::endl;
					_currentPlayerMovement[1] = 1.0;
				}
				if (this->_playerMovement->right)
				{
					//std::cout << "Player is going right" << std::endl;
					_currentPlayerMovement[2] = 1.0;
				}
				if (this->_playerMovement->left)
				{
					//std::cout << "Player is going left" << std::endl;
					_currentPlayerMovement[3] = 1.0;
				}
			}
		};
	}
}