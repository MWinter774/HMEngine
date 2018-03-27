#pragma once
#include "Collider.h"

namespace HMEngine
{
	namespace Core
	{
		namespace Physics
		{
			namespace Colliders
			{
				class BoundingCapsule : public HMEngine::Core::Physics::Colliders::Collider
				{
				public:
					BoundingCapsule(float mass);
					BoundingCapsule(float mass, float height, float radius);
					~BoundingCapsule();

					inline HMEngine::Components::Component* Clone() override { return new HMEngine::Core::Physics::Colliders::BoundingCapsule(*this); }

					void Initialize() override;

				private:
					float _height;
					float _radius;
				};
			}
		}
	}
}