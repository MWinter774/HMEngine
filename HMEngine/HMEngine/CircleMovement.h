#pragma once
#include "Component.h"
#include <vector>

namespace HMEngine
{
	namespace Components
	{
		class CircleMovement : public HMEngine::Components::Component
		{
		public:
			CircleMovement(float xCenter, float yCenter, float radius);
			~CircleMovement();
			CircleMovement(const HMEngine::Components::CircleMovement& other);
			HMEngine::Components::CircleMovement& operator=(const HMEngine::Components::CircleMovement& other);

			inline HMEngine::Components::Component* Clone() override { return new HMEngine::Components::CircleMovement(*this); }
			void UpdateEvent() override;

		private:
			std::vector<std::pair<float, float>> _circlePoints;
			unsigned int _i;
		};
	}
}