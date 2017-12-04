#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		class Transform;
		namespace Rendering
		{
			class Camera
			{
			public:
				static HMEngine::Core::Rendering::Camera& GetInstance();

				/* Getters/Setters/Adders for position */
				float GetPositionX() const { return this->_transform->GetPositionX(); }
				float GetPositionY() const { return this->_transform->GetPositionY(); }
				float GetPositionZ() const { return this->_transform->GetPositionZ(); }
				glm::vec3 GetPosition() const { return this->_transform->GetPosition(); }
				void SetPositionX(float x) { this->_transform->SetPositionX(x); }
				void SetPositionY(float y) { this->_transform->SetPositionY(y); }
				void SetPositionZ(float z) { this->_transform->SetPositionZ(z); }
				void SetPosition(const glm::vec3& pos) { this->_transform->SetPosition(pos); }
				void SetPosition(float x, float y, float z) { this->_transform->SetPosition(x, y, z); }
				void AddPositionX(float x) { this->_transform->AddPositionX(x); };
				void AddPositionY(float y) { this->_transform->AddPositionY(y); };
				void AddPositionZ(float z) { this->_transform->AddPositionZ(z); };
				void AddPosition(const glm::vec3& pos) { this->_transform->AddPosition(pos); }
				void AddPosition(float x, float y, float z) { this->_transform->AddPosition(x, y, z); }

				glm::mat4 GetViewMatrix() const;

			private:
				Camera();
				Camera(const HMEngine::Core::Rendering::Camera& other) = delete;
				HMEngine::Core::Rendering::Camera& operator=(HMEngine::Core::Rendering::Camera& other) = delete;
				~Camera();

				HMEngine::Core::Transform* _transform;
				glm::vec3 _forward;
				glm::vec3 _up;
			};
		}
	}
}