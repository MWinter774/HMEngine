#pragma once
#include "Component.h"
#include "bullet\btBulletDynamicsCommon.h"

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
					Collider();
					virtual ~Collider();

					void AttachToGameObjectEvent() override;

					virtual void Initialize() = 0;

				protected:
					btCollisionShape* _collider;
					btRigidBody* _rigidBody;
				};
			}
		}
	}
}