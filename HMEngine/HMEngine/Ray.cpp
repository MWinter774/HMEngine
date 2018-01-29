#include "Ray.h"

HMEngine::Core::Physics::Ray::Ray(const glm::vec3& origin, const glm::vec3& direction) : _origin(origin), _direction(direction)
{
}

HMEngine::Core::Physics::Ray::~Ray()
{
}