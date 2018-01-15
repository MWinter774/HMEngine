#include "BaseLight.h"

HMEngine::Components::BaseLight::BaseLight(glm::vec3 color, float intensity) : _color(color), _intensity(intensity)
{

}



HMEngine::Components::BaseLight& HMEngine::Components::BaseLight::operator=(HMEngine::Components::BaseLight& other)
{
	if (this != &other)
	{
		this->SetColor(other.GetColor());
		this->SetIntensity(other.GetIntensity());
	}
	return *this;
}
