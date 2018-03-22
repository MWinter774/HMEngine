#pragma once
#include "glm\glm.hpp"
#include <unordered_set>
#include "bullet\btBulletDynamicsCommon.h"

namespace HMEngine
{
	namespace Core
	{
		class GameObject;

		namespace Physics
		{
			namespace Colliders
			{
				class Collider;
			}
			class Ray;
			class RaycastInfo;

			class PhysicsEngine
			{
				typedef struct
				{
					btBroadphaseInterface* broadphase;
					btDefaultCollisionConfiguration* collisionConfiguration;
					btCollisionDispatcher* dispatcher;
					btSequentialImpulseConstraintSolver* solver;
					btDiscreteDynamicsWorld* dynamicsWorld;
				} BulletData;
			public:
				static HMEngine::Core::Physics::RaycastInfo Raycast(const glm::vec3& origin, const glm::vec3& direction, float maxDistance);
				static HMEngine::Core::Physics::RaycastInfo Raycast(const HMEngine::Core::Physics::Ray& ray);

				static void AddGameObjectCollider(HMEngine::Core::Physics::Colliders::Collider* collider);
				static void RemoveGameObjectCollider(HMEngine::Core::Physics::Colliders::Collider* collider);

				static void Initialize();
				static void Destroy();

				inline static BulletData& GetBulletData() { return PhysicsEngine::_bulletData; }

			private:
				PhysicsEngine() = delete;
				~PhysicsEngine() = delete;
				PhysicsEngine(const HMEngine::Core::Physics::PhysicsEngine& other) = delete;
				HMEngine::Core::Physics::PhysicsEngine& operator=(const HMEngine::Core::Physics::PhysicsEngine& other) = delete;

				static std::unordered_set<HMEngine::Core::Physics::Colliders::Collider*> _gameObjectColliders;

				static BulletData _bulletData;
			};
		}
	}
}