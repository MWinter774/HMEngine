#pragma once
#include <glm\glm.hpp>

namespace HMEngine
{
	namespace Components
	{
		class BaseLight
		{
		public:
			BaseLight() : _color(1, 1, 1), _intensity(0.5f) {};
			BaseLight(glm::vec3 color, float intenstity);
			~BaseLight() {};

			inline glm::vec3 GetColor() const { return this->_color; }
			inline float GetIntensity() const { return this->_intensity; }

			inline void SetColor(const glm::vec3& color) { this->_color = color; }
			inline void SetIntensity(float intensity) { this->_intensity = intensity; }

		private:
			glm::vec3 _color;
			float _intensity;


		};
	}
}

