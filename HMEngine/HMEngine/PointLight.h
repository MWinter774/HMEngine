#pragma once
#include "Component.h"
#include "BaseLight.h"
#include "GameObject.h"
#include "Transform.h"

namespace HMEngine
{
	namespace Components
	{
		class PointLight : public HMEngine::Components::Component
		{
		public:
			PointLight(const HMEngine::Components::BaseLight& base, const glm::vec3& attenuation, float range);
			~PointLight();
			PointLight(const HMEngine::Components::PointLight& other);
			HMEngine::Components::PointLight& operator=(const HMEngine::Components::PointLight& other);

			inline HMEngine::Components::Component* Clone() override { return new HMEngine::Components::PointLight(*this); }
			void AttachToGameObjectEvent() override;

			inline HMEngine::Components::BaseLight& GetBase() const { return *this->_base; }
			inline glm::vec3 GetAttenuation() const { return this->_attenuation; }
			inline float GetRange() const { return this->_range; }
			inline glm::vec3 GetPosition() const { return this->_parentObject->GetTransform().GetPosition(); }

			inline void SetBase(const HMEngine::Components::BaseLight& base) { *this->_base = base; }
			inline void SetAttenuation(const glm::vec3& attenuation) { this->_attenuation = attenuation; }
			inline void SetRange(float range) { this->_range = range; }
			inline void SetPosition(const glm::vec3& position) { this->_parentObject->GetTransform().SetPosition(position); }

		private:
			HMEngine::Components::BaseLight* _base;
			glm::vec3 _attenuation;
			float _range;

		};
	}
}