#pragma once
#include "glm\glm.hpp"
#include <unordered_map>

namespace HMEngine
{
	namespace Core
	{
		class GameObject;

		namespace Physics
		{
			class Ray;
			class BoundingSphere;
			class RaycastInfo;

			class PhysicsEngine
			{
			public:
				static HMEngine::Core::Physics::RaycastInfo Raycast(const glm::vec3& origin, const glm::vec3& direction, float maxDistance);
				static HMEngine::Core::Physics::RaycastInfo Raycast(const HMEngine::Core::Physics::Ray& ray, float maxDistance);

				static void AddGameObjectCollider(HMEngine::Core::Physics::BoundingSphere* boundingSphere, HMEngine::Core::GameObject* gameObject);
				static void RemoveGameObjectCollider(HMEngine::Core::Physics::BoundingSphere* boundingSphere);

			private:
				PhysicsEngine() = delete;
				~PhysicsEngine() = delete;
				PhysicsEngine(const HMEngine::Core::Physics::PhysicsEngine& other) = delete;
				HMEngine::Core::Physics::PhysicsEngine& operator=(const HMEngine::Core::Physics::PhysicsEngine& other) = delete;

				static std::unordered_map<HMEngine::Core::Physics::BoundingSphere*, HMEngine::Core::GameObject*> _gameObjectColliders;
			};
		}
	}
}