#include "DirectionalLight.h"
#include "BasicShader.h"
#include "GameObject.h"
#include "BaseLight.h"
#include "RenderingEngine.h"

HMEngine::Components::DirectionalLight::DirectionalLight(const HMEngine::Components::BaseLight& base, const glm::vec3& direction) : _direction(glm::normalize(direction)), _base(new HMEngine::Components::BaseLight(base))
{
}

HMEngine::Components::DirectionalLight::~DirectionalLight()
{
	delete this->_base;
	if (this->_isAttachedToGameObject)
		HMEngine::Core::Rendering::RenderingEngine::GetInstance().RemoveDirectionalLight(*this);
}

HMEngine::Components::DirectionalLight::DirectionalLight(const HMEngine::Components::DirectionalLight& other) : _direction(other._direction), _base(new HMEngine::Components::BaseLight(*other._base))
{
}

void HMEngine::Components::DirectionalLight::AttachToGameObjectEvent()
{
	HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddDirectionalLight(*this);
}

HMEngine::Components::DirectionalLight& HMEngine::Components::DirectionalLight::operator=(HMEngine::Components::DirectionalLight& other)
{
	if (this != &other)
	{
		delete this->_base;
		this->_base = new HMEngine::Components::BaseLight(*other._base);
		this->_direction = other._direction;
	}
	return *this;
}

bool HMEngine::Components::DirectionalLight::operator==(HMEngine::Components::DirectionalLight& other)
{
	return this == &other;
}