#include "Camera.h"

HMEngine::Core::Rendering::Camera& HMEngine::Core::Rendering::Camera::GetInstance()
{
	static HMEngine::Core::Rendering::Camera& instance = HMEngine::Core::Rendering::Camera();
	return instance;
}

HMEngine::Core::Rendering::Camera::Camera()
{
}

HMEngine::Core::Rendering::Camera::~Camera()
{
	if (this->_transform != nullptr)
		delete this->_transform;
}