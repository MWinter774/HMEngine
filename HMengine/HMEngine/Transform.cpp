#include "Transform.h"

glm::mat4 HMEngine::Core::Transform::projectionMatrix = glm::perspective(glm::radians(HMEngine::GameEngine::GetFov()), float(HMEngine::GameEngine::GetWindowWidth()) / float(HMEngine::GameEngine::GetWindowHeight()), HMEngine::GameEngine::GetZNear(), HMEngine::GameEngine::GetZFar());

/*
Updates the projection matrix.
*/
void HMEngine::Core::Transform::UpdateProjectionMatrix()
{
	HMEngine::Core::Transform::projectionMatrix = glm::perspective(glm::radians(HMEngine::GameEngine::GetFov()), float(HMEngine::GameEngine::GetWindowWidth()) / float(HMEngine::GameEngine::GetWindowHeight()), HMEngine::GameEngine::GetZNear(), HMEngine::GameEngine::GetZFar());
}

HMEngine::Core::Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : _position(position), _rotation(rotation), _scale(scale)
{
}

HMEngine::Core::Transform::~Transform()
{
}

HMEngine::Core::Transform HMEngine::Core::Transform::operator=(const Transform& transform)
{
	this->_position = transform._position;
	this->_rotation = transform._rotation;
	this->_scale = transform._scale;

	return *this;
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
Returns the view matrix.
*/
glm::mat4 HMEngine::Core::Transform::GetViewMatrix() const
{
	return HMEngine::Core::Rendering::Camera::GetInstance().GetViewMatrix();
}

/*
Returns the projection matrix.
*/
glm::mat4 HMEngine::Core::Transform::GetProjectionMatrix() const
{
	return HMEngine::Core::Transform::projectionMatrix;
}

/*
Calculates and returns the MVP matrix.
*/
glm::mat4 HMEngine::Core::Transform::GetMVPMatrix() const
{
	return this->GetProjectionMatrix() * this->GetViewMatrix() * this->GetModelMatrix();
}

