#include "Camera.h"
#include "Transform.h"
#include "GameSettings.h"
#include "Ray.h"
#include "glm\gtc\matrix_transform.hpp"

HMEngine::Core::Rendering::Camera& HMEngine::Core::Rendering::Camera::GetInstance()
{
	static HMEngine::Core::Rendering::Camera& instance = HMEngine::Core::Rendering::Camera();
	return instance;
}

void HMEngine::Core::Rendering::Camera::Update()
{
	this->_viewMatrix = glm::lookAt(this->_transform->GetPosition(), this->_transform->GetPosition() + this->_forward, this->_up);
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
HMEngine::Core::Physics::Ray HMEngine::Core::Rendering::Camera::GetRayFromScreenPoint(const glm::vec2& screenPos)
{
	glm::vec2 normalizedPoints = this->GetNormalizedCoords(screenPos);
	glm::vec4 clipCoords = glm::vec4(normalizedPoints, -1.0f, 1.0f);
	glm::vec4 eyeCoords = this->ConvertToEyeCoords(clipCoords);
	glm::vec3 direction = this->ConvertToWorldCoords(eyeCoords);

	return HMEngine::Core::Physics::Ray(this->_transform->GetPosition(), direction);
}

inline glm::mat4 HMEngine::Core::Rendering::Camera::GetMVP() const
{
	return this->_transform->GetMVPMatrix();
}

HMEngine::Core::Rendering::Camera::Camera() : _transform(new HMEngine::Core::Transform()), _forward(HMEngine::GameSettings::Z_AXIS), _up(HMEngine::GameSettings::Y_AXIS), _right(), _windowWidth(HMEngine::GameSettings::GetWindowWidth()), _windowHeight(HMEngine::GameSettings::GetWindowHeight()), _projectionMatrix(HMEngine::GameSettings::GetProjectionMatrix())
{
}

HMEngine::Core::Rendering::Camera::~Camera()
{
	if (this->_transform != nullptr)
		delete this->_transform;
}

glm::vec4 HMEngine::Core::Rendering::Camera::ConvertToEyeCoords(const glm::vec4& coords) const
{
	glm::vec4 eyeCoords = glm::inverse(this->_projectionMatrix) * coords;
	return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
}

glm::vec3 HMEngine::Core::Rendering::Camera::ConvertToWorldCoords(const glm::vec4& coords) const
{
	glm::vec4 worldCoords = glm::inverse(this->_viewMatrix) * coords;
	glm::vec3 ray = glm::normalize(glm::vec3(worldCoords.x, worldCoords.y, worldCoords.z));
	return ray;
}