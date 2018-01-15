#pragma once
#include <glm\glm.hpp>
#include "Component.h"

namespace HMEngine
{
	namespace Components
	{

		class BaseLight : public HMEngine::Components::Component
		{
		public:
			BaseLight() {};
			BaseLight(glm::vec3 color, float intenstity);
			~BaseLight() {};

			glm::vec3 GetColor() const { return this->_color; };
			float GetIntensity() const { return this->_intensity; };

			void SetColor(glm::vec3 color) { this->_color = color; };
			void SetIntensity(float intensity) { this->_intensity = intensity; };

			HMEngine::Components::BaseLight& operator=(HMEngine::Components::BaseLight& other);
			inline HMEngine::Components::BaseLight* Clone() override { return new HMEngine::Components::BaseLight(*this); }



		private:
			glm::vec3 _color;
			float _intensity = 0;


		};
	}
}

