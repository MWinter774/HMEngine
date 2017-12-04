#include "Camera.h"

HMEngine::Core::Rendering::Camera& HMEngine::Core::Rendering::Camera::GetInstance()
{
	static HMEngine::Core::Rendering::Camera& instance = HMEngine::Core::Rendering::Camera();
	return instance;
}

glm::mat4 HMEngine::Core::Rendering::Camera::GetViewMatrix() const
{
	return glm::lookAt(this->_transform->GetPosition(), this->_transform->GetPosition() + this->_forward, this->_up);
}

HMEngine::Core::Rendering::Camera::Camera() : _transform(new HMEngine::Core::Transform()), _forward(HMEngine::Constants::Z_AXIS), _up(HMEngine::Constants::Y_AXIS)
{
}

HMEngine::Core::Rendering::Camera::~Camera()
{
	if (this->_transform != nullptr)
		delete this->_transform;
}