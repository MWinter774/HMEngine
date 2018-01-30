#include "RaycastInfo.h"
#include "GameObject.h"
#include "Transform.h"

HMEngine::Core::Physics::RaycastInfo::RaycastInfo() : isHit(false), hits(), ray(glm::vec3(-1), glm::vec3(-1))
{
}

HMEngine::Core::Physics::RaycastInfo::~RaycastInfo()
{
}

glm::vec3 HMEngine::Core::Physics::RaycastInfo::GetEndPoint(float distance) const
{
	glm::vec3 rayOrigin = this->ray.GetOrigin();
	glm::vec3 rayDirection = this->ray.GetDirection();
	float rayLength = sqrt(rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y + rayDirection.z * rayDirection.z);
	glm::vec3 deltaVector = rayDirection / rayLength;
	glm::vec3 endPoint = rayOrigin + distance * deltaVector;

	return endPoint;
}
