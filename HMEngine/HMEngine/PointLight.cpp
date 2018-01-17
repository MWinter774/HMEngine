#include "PointLight.h"
#include "RenderingEngine.h"

HMEngine::Components::PointLight::PointLight(const HMEngine::Components::BaseLight& base, const glm::vec3& attenuation, float range) : _base(new HMEngine::Components::BaseLight(base)), _attenuation(attenuation), _range(range)
{
}

HMEngine::Components::PointLight::~PointLight()
{
	delete this->_base;
	if (this->_isAttachedToGameObject)
		HMEngine::Core::Rendering::RenderingEngine::GetInstance().RemovePointLight(*this);
}

HMEngine::Components::PointLight::PointLight(const HMEngine::Components::PointLight& other) : _base(new HMEngine::Components::BaseLight(*other._base)), _attenuation(other._attenuation), _range(other._range)
{
}

HMEngine::Components::PointLight& HMEngine::Components::PointLight::operator=(const HMEngine::Components::PointLight& other)
{
	if (this != &other)
	{
		delete this->_base;
		this->_base = new HMEngine::Components::BaseLight(*other._base);
		this->_attenuation = other._attenuation;
		this->_range = other._range;
	}

	return *this;
}

void HMEngine::Components::PointLight::AttachToGameObjectEvent()
{
	HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddPointLight(*this);
}