#include "Transform.h"

HMEngine::Core::Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : _position(position), _rotation(rotation), _scale(scale)
{
}

HMEngine::Core::Transform::~Transform()
{
}

/*
Calculates and returns the model matrix.
*/
glm::mat4 HMEngine::Core::Transform::GetModelMatrix() const
{
	glm::mat4 rotX = glm::rotate(this->_rotation.x, HMEngine::Constants::X_AXIS);
	glm::mat4 rotY = glm::rotate(this->_rotation.y, HMEngine::Constants::Y_AXIS);
	glm::mat4 rotZ = glm::rotate(this->_rotation.z, HMEngine::Constants::Z_AXIS);

	glm::mat4 translationMatrix = glm::translate(this->_position);
	glm::mat4 rotationMatrix = rotX * rotY * rotZ;
	glm::mat4 scaleMatrix = glm::scale(this->_scale);

	return translationMatrix * rotationMatrix * scaleMatrix;
}

/*
Calculates and returns the view matrix.
*/
glm::mat4 HMEngine::Core::Transform::GetViewMatrix() const
{
	return glm::mat4();
}

/*
Calculates and returns the projection matrix.
*/
glm::mat4 HMEngine::Core::Transform::GetProjectionMatrix() const
{
	return glm::mat4();
}

/*
Calculates and returns the MVP matrix.
*/
glm::mat4 HMEngine::Core::Transform::GetMVPMatrix() const
{
	return this->GetProjectionMatrix() * this->GetViewMatrix() * this->GetModelMatrix();
}
