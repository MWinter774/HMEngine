#pragma once
#include "glm\glm.hpp"
#include "Collider.h"

namespace HMEngine
{
	namespace Core
	{
		namespace Physics
		{
			namespace Colliders
			{
				class BoundingSphere : public HMEngine::Core::Physics::Colliders::Collider
				{
				public:
					BoundingSphere(float mass);
					BoundingSphere(float mass, const glm::vec3& center, float radius);
					~BoundingSphere();

					inline HMEngine::Components::Component* Clone() override { return new HMEngine::Core::Physics::Colliders::BoundingSphere(*this); }

					inline glm::vec3 GetCenter() const { return this->_center; }
					inline float GetRadius() const { return this->_radius; }

					void Initialize() override;

				private:
					glm::vec3 _center;
					float _radius;
				};
			}
		}
	}
}