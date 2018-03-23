#pragma once
#include <glm\glm.hpp>
#include "Collider.h"

namespace HMEngine
{
	namespace Core
	{
		namespace Physics
		{
			namespace Colliders
			{
				class BoundingPlane : public HMEngine::Core::Physics::Colliders::Collider
				{
				public:
					BoundingPlane(float mass);
					~BoundingPlane();

					inline HMEngine::Components::Component* Clone() override { return new HMEngine::Core::Physics::Colliders::BoundingPlane(*this); }

					void Initialize() override;
				};
			}
		}
	}
}