#include "PhysicsEngine.h"
#include "Ray.h"

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
	return false;
}
