#include "PhysicsEngine.h"
#include "Ray.h"
#include "BoundingSphere.h"
#include "GameObject.h"
#include "Transform.h"
#include "RaycastInfo.h"

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
HMEngine::Core::Physics::RaycastInfo HMEngine::Core::Physics::PhysicsEngine::Raycast(const glm::vec3& origin, const glm::vec3& direction, float maxDistance)
{
	return HMEngine::Core::Physics::RaycastInfo();
}

/*
Returns whether the ray is colliding with some object.
Input:
ray - the ray
maxDistance - maximum distance of the ray
Output:
True if ray hitting some object, false otherwise.
*/
HMEngine::Core::Physics::RaycastInfo HMEngine::Core::Physics::PhysicsEngine::Raycast(const HMEngine::Core::Physics::Ray& ray, float maxDistance)
{
	HMEngine::Core::Physics::RaycastInfo info = HMEngine::Core::Physics::RaycastInfo();
	info.ray = ray;

	glm::vec3 rayDirection = ray.GetDirection();
	glm::vec3 rayOrigin = ray.GetOrigin();
	float rayLength = sqrt(rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y + rayDirection.z * rayDirection.z);
	float vLen = maxDistance / 10.0f;

	float b = 0.0f;
	float c = 0.0f;
	float res = 0.0f;
	glm::vec3 center;
	float radius = 0.0f;
	glm::vec3 distance;
	HMEngine::Core::Physics::BoundingSphere* boundingSphere = nullptr;
	glm::vec3 deltaVector;
	glm::vec3 endPoint;
	for (auto item : HMEngine::Core::Physics::PhysicsEngine::_gameObjectColliders)
	{
		boundingSphere = item.first;
		radius = boundingSphere->GetRadius();
		center = boundingSphere->GetCenter() + item.second->GetTransform().GetPosition();
		distance = rayOrigin - center;

		b = glm::dot(rayDirection, distance);
		c = glm::dot(distance, distance) - radius * radius;
		res = b * b - c;
		if (res >= 0)
		{
			//deltaVector = rayDirection / rayLength;
			//endPoint = rayOrigin + vLen * deltaVector;

			//item.second->GetTransform().SetPosition(endPoint);
			//isColliding = true;
			info.isHit = true;
			info.hits.emplace(glm::distance(rayOrigin, center), item.second);
		}
	}
	return info;
}

void HMEngine::Core::Physics::PhysicsEngine::AddGameObjectCollider(HMEngine::Core::Physics::BoundingSphere* boundingSphere, HMEngine::Core::GameObject* gameObject)
{
	HMEngine::Core::Physics::PhysicsEngine::_gameObjectColliders[boundingSphere] = gameObject;
}

void HMEngine::Core::Physics::PhysicsEngine::RemoveGameObjectCollider(HMEngine::Core::Physics::BoundingSphere* boundingSphere)
{
	HMEngine::Core::Physics::PhysicsEngine::_gameObjectColliders.erase(boundingSphere);
}
