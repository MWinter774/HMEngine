#pragma once
#include "BaseLight.h"
#include <glm\glm.hpp>


namespace HMEngine
{
	namespace Components
	{

		class DirectionalLight : public HMEngine::Components::BaseLight
		{
		public:
			DirectionalLight(HMEngine::Components::BaseLight& base, glm::vec3 direction);
			~DirectionalLight() {};

			void HMEngine::Components::DirectionalLight::UpdateEvent();
			HMEngine::Components::DirectionalLight& operator=(HMEngine::Components::DirectionalLight& other);
			inline HMEngine::Components::DirectionalLight* Clone() override { return new HMEngine::Components::DirectionalLight(*this); }

			//virtual void RenderEvent() override;

			HMEngine::Components::BaseLight* GetBase() const { return this->_base; };
			glm::vec3 GetDirection() const { return this->_direction; };

			void SetBase(HMEngine::Components::BaseLight& base) { this->_base = &base; };
			void SetDirection(glm::vec3 direction) { this->_direction = direction; };




		private:
			HMEngine::Components::BaseLight* _base;
			glm::vec3 _direction;
		};
	}
}

