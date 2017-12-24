#include "Camera.h"

HMEngine::Core::Rendering::Camera& HMEngine::Core::Rendering::Camera::GetInstance()
{
	static HMEngine::Core::Rendering::Camera& instance = HMEngine::Core::Rendering::Camera();
	return instance;
}

#pragma region Getters/Setters/Adders for position
float HMEngine::Core::Rendering::Camera::GetPositionX() const
{
	return this->_transform->GetPositionX();
}

float HMEngine::Core::Rendering::Camera::GetPositionY() const
{
	return this->_transform->GetPositionY();
}

float HMEngine::Core::Rendering::Camera::GetPositionZ() const
{
	return this->_transform->GetPositionZ();
}

glm::vec3 HMEngine::Core::Rendering::Camera::GetPosition() const
{
	return this->_transform->GetPosition();
}

void HMEngine::Core::Rendering::Camera::SetPositionX(float x)
{
	this->_transform->SetPositionX(x);
}

void HMEngine::Core::Rendering::Camera::SetPositionY(float y)
{
	this->_transform->SetPositionY(y);
}

void HMEngine::Core::Rendering::Camera::SetPositionZ(float z)
{
	this->_transform->SetPositionZ(z);
}

void HMEngine::Core::Rendering::Camera::SetPosition(const glm::vec3 & pos)
{
	this->_transform->SetPosition(pos);
}

void HMEngine::Core::Rendering::Camera::SetPosition(float x, float y, float z)
{
	this->_transform->SetPosition(x, y, z);
}

void HMEngine::Core::Rendering::Camera::AddPositionX(float x)
{
	this->_transform->AddPositionX(x);
}

void HMEngine::Core::Rendering::Camera::AddPositionY(float y)
{
	this->_transform->AddPositionY(y);
}

void HMEngine::Core::Rendering::Camera::AddPositionZ(float z)
{
	this->_transform->AddPositionZ(z);
}

void HMEngine::Core::Rendering::Camera::AddPosition(const glm::vec3 & pos)
{
	this->_transform->AddPosition(pos);
}

void HMEngine::Core::Rendering::Camera::AddPosition(float x, float y, float z)
{
	this->_transform->AddPosition(x, y, z);
}
#pragma endregion

/*
Calculates and returns the view matrix.
*/
glm::mat4 HMEngine::Core::Rendering::Camera::GetViewMatrix()
{
	return glm::lookAt(this->_transform->GetPosition(), this->_transform->GetPosition() + this->_forward, this->_up);
}

glm::mat4 HMEngine::Core::Rendering::Camera::GetMVP() const
{
	return this->_transform->GetMVPMatrix();
}


HMEngine::Core::Rendering::Camera::Camera() : _transform(new HMEngine::Core::Transform()), _forward(HMEngine::Constants::Z_AXIS), _up(HMEngine::Constants::Y_AXIS)
{
}

HMEngine::Core::Rendering::Camera::~Camera()
{
	if (this->_transform != nullptr)
		delete this->_transform;
}