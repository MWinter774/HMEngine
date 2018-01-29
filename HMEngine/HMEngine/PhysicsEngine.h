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

			class PhysicsEngine
			{
			public:
				static bool Raycast(const glm::vec3& origin, const glm::vec3& direction, float maxDistance);
				static bool Raycast(const HMEngine::Core::Physics::Ray& ray, float maxDistance);

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