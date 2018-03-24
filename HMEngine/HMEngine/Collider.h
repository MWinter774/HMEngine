#pragma once
#include "Component.h"
#include "bullet\btBulletDynamicsCommon.h"
#include "glm\glm.hpp"

namespace HMEngine
{
	namespace Core
	{
		namespace Physics
		{
			class PhysicsEngine;

			namespace Colliders
			{
				class Collider : public HMEngine::Components::Component
				{
					friend class PhysicsEngine;
				public:
					Collider(float mass);
					virtual ~Collider();

					void AttachToGameObjectEvent() override;

					void ApplyForce(const glm::vec3& force);

					inline btRigidBody* GetRigidBody() const { return this->_rigidBody; }

					virtual void Initialize() = 0;

				protected:
					btCollisionShape* _collider;
					btRigidBody* _rigidBody;
					float _mass;
				};
			}
		}
	}
}