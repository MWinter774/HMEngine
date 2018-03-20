#include "RaycastInfo.h"
#include "GameObject.h"
#include "Transform.h"
#include "Component.h"

HMEngine::Core::Physics::RaycastInfo::RaycastInfo() : isHit(false), hits(), ray(glm::vec3(-1), glm::vec3(-1))
{
}

HMEngine::Core::Physics::RaycastInfo::~RaycastInfo()
{
}

/*
Returns the point that is far away from the ray origin by the amount that stored in distance.
Input:
distance - how far away the point is from the ray origin
Output:
Point that is far away from the ray origin by the amount that is stored in distance.
*/
glm::vec3 HMEngine::Core::Physics::RaycastInfo::GetEndPoint(float distance) const
{
	glm::vec3 rayOrigin = this->ray.GetOrigin();
	glm::vec3 rayDirection = this->ray.GetDirection();
	float rayLength = sqrt(rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y + rayDirection.z * rayDirection.z);
	glm::vec3 deltaVector = rayDirection / rayLength;
	glm::vec3 endPoint = rayOrigin + distance * deltaVector;

	return endPoint;
}

bool HMEngine::Core::Physics::RaycastInfo::HasObject(HMEngine::Components::Component& component)
{
	const HMEngine::Core::GameObject* parentObject = &component.GetParent();
	for (auto& pair : this->hits)
	{
		if (pair.second == parentObject)
		{
			return true;
		}
	}

	return false;
}
