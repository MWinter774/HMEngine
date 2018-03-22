#pragma once
#include <glm\glm.hpp>
#include <vector>
#include "bullet\btBulletDynamicsCommon.h"
#include "Collider.h"

namespace HMEngine
{
	namespace Core
	{
		namespace Physics
		{
			class IntersectionData;

			namespace Colliders
			{
				class BoundingSphere : public HMEngine::Core::Physics::Colliders::Collider
				{
				public:
					BoundingSphere();
					BoundingSphere(const glm::vec3& center, float radius);
					~BoundingSphere();
					BoundingSphere(const HMEngine::Core::Physics::Colliders::BoundingSphere& other);
					HMEngine::Core::Physics::Colliders::BoundingSphere& operator=(const HMEngine::Core::Physics::Colliders::BoundingSphere& other);

					inline HMEngine::Components::Component* Clone() override { return new HMEngine::Core::Physics::Colliders::BoundingSphere(*this); }

					HMEngine::Core::Physics::IntersectionData IsIntersect(const HMEngine::Core::Physics::Colliders::BoundingSphere& other);

					inline glm::vec3 GetCenter() const { return this->_center; }
					inline float GetRadius() const { return this->_radius; }

					void Initialize() override;

				private:
					glm::vec3 _center;
					float _radius;
					btSphereShape* _collider;
					btRigidBody* _rigidBody;
				};
			}
		}
	}
}