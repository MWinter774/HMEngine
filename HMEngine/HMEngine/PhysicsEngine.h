#pragma once
#include "glm\glm.hpp"
#include <vector>
#include <unordered_map>
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

				static void Update();

				inline static BulletData& GetBulletData() { return PhysicsEngine::_bulletData; }

				inline static void AddCollisionShape(btCollisionShape* collisionShape) { HMEngine::Core::Physics::PhysicsEngine::_collisionShapes.push_back(collisionShape); }

			private:
				PhysicsEngine() = delete;
				~PhysicsEngine() = delete;
				PhysicsEngine(const HMEngine::Core::Physics::PhysicsEngine& other) = delete;
				HMEngine::Core::Physics::PhysicsEngine& operator=(const HMEngine::Core::Physics::PhysicsEngine& other) = delete;

				static std::unordered_map<HMEngine::Core::Physics::Colliders::Collider*, HMEngine::Core::GameObject*> _gameObjectColliders;
				static std::unordered_map<btRigidBody*, HMEngine::Core::GameObject*> _rigidBodies;

				static BulletData _bulletData;

				static std::vector<btCollisionShape*> _collisionShapes;

				static float RoundNumber(float x);
			};
		}
	}
}