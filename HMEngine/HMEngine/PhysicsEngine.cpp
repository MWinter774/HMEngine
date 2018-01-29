#include "PhysicsEngine.h"
#include "Ray.h"
#include "BoundingSphere.h"
#include "GameObject.h"
#include "Transform.h"

std::unordered_map<HMEngine::Core::Physics::BoundingSphere*, HMEngine::Core::GameObject*> HMEngine::Core::Physics::PhysicsEngine::_gameObjectColliders;

/*
Returns whether the ray is colling with some object.
Input:
origin - Initial position of the ray
direction - direction of the ray
maxDistance - maximum distance of the ray
Output:
True if ray hitting some object, false otherwise.
*/
bool HMEngine::Core::Physics::PhysicsEngine::Raycast(const glm::vec3& origin, const glm::vec3& direction, float maxDistance)
{
	return false;
}

/*
Returns whether the ray is colliding with some object.
Input:
ray - the ray
maxDistance - maximum distance of the ray
Output:
True if ray hitting some object, false otherwise.
*/
bool HMEngine::Core::Physics::PhysicsEngine::Raycast(const HMEngine::Core::Physics::Ray& ray, float maxDistance)
{
	bool isColliding = false;
	glm::vec3 rayDirection = glm::normalize(ray.GetDirection());
	glm::vec3 rayOrigin = ray.GetOrigin();
	for (auto item : HMEngine::Core::Physics::PhysicsEngine::_gameObjectColliders)
	{
		glm::vec3 center = item.first->GetCenter() + item.second->GetTransform().GetPosition();
		float b = glm::dot(rayDirection, rayOrigin - center);
		float c = glm::dot(rayOrigin - center, rayOrigin - center) - item.first->GetRadius() * item.first->GetRadius();
		float res = b * b - c;
		if (res >= 0)
		{
			isColliding = true;
		}
	}
	return isColliding;
}

void HMEngine::Core::Physics::PhysicsEngine::AddGameObjectCollider(HMEngine::Core::Physics::BoundingSphere* boundingSphere, HMEngine::Core::GameObject* gameObject)
{
	HMEngine::Core::Physics::PhysicsEngine::_gameObjectColliders[boundingSphere] = gameObject;
}

void HMEngine::Core::Physics::PhysicsEngine::RemoveGameObjectCollider(HMEngine::Core::Physics::BoundingSphere* boundingSphere)
{
	HMEngine::Core::Physics::PhysicsEngine::_gameObjectColliders.erase(boundingSphere);
}
