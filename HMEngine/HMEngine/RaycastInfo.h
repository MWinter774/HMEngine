#pragma once
#include "glm\glm.hpp"
#include <set>
#include "Ray.h"

namespace HMEngine
{
	namespace Components
	{
		class Component;
	}

	namespace Core
	{
		class GameObject;
		namespace Physics
		{
			class RaycastInfo
			{
			public:
				RaycastInfo();
				~RaycastInfo();
				inline operator bool() const { return this->isHit; }

				glm::vec3 GetEndPoint(float distance) const;

				bool HasObject(HMEngine::Components::Component& component);

				bool isHit; //did the ray hit something
				std::set<std::pair<float, HMEngine::Core::GameObject*>> hits; //list of pairs, first item in pair is the distance to the game object, second item is the GameObject
				HMEngine::Core::Physics::Ray ray; //the ray
			};
		}
	}
}