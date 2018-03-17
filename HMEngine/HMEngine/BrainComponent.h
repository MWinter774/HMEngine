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
		};
	}
}