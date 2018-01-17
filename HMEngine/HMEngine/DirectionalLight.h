#pragma once
#include "BaseLight.h"
#include "Component.h"
#include <glm\glm.hpp>


namespace HMEngine
{
	namespace Components
	{
		class DirectionalLight : public HMEngine::Components::Component
		{
		public:
			DirectionalLight(const HMEngine::Components::BaseLight& base, const glm::vec3& direction);
			~DirectionalLight();
			DirectionalLight(const HMEngine::Components::DirectionalLight& other);
			bool operator==(HMEngine::Components::DirectionalLight& other);
			HMEngine::Components::DirectionalLight& operator=(HMEngine::Components::DirectionalLight& other);

			void AttachToGameObjectEvent() override;

			inline HMEngine::Components::DirectionalLight* Clone() override { return new HMEngine::Components::DirectionalLight(*this); }

			inline HMEngine::Components::BaseLight& GetBase() const { return *this->_base; }
			inline glm::vec3 GetDirection() const { return this->_direction; };

			inline void SetBase(const HMEngine::Components::BaseLight& base) { *this->_base = base; };
			inline void SetDirection(const glm::vec3& direction) { this->_direction = direction; };

		private:
			HMEngine::Components::BaseLight* _base;
			glm::vec3 _direction;
		};
	}
}

