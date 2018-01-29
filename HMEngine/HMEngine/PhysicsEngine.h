#pragma once
#include "glm\glm.hpp"

namespace HMEngine
{
	namespace Core
	{
		namespace Physics
		{
			class Ray;

			class PhysicsEngine
			{
			public:
				static bool Raycast(const glm::vec3& origin, const glm::vec3& direction, float maxDistance);
				static bool Raycast(const HMEngine::Core::Physics::Ray& ray, float maxDistance);

			private:
				PhysicsEngine() = delete;
				~PhysicsEngine() = delete;
				PhysicsEngine(const HMEngine::Core::Physics::PhysicsEngine& other) = delete;
				HMEngine::Core::Physics::PhysicsEngine& operator=(const HMEngine::Core::Physics::PhysicsEngine& other) = delete;
			};
		}
	}
}