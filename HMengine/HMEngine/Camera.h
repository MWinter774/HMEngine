#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine::Core
{
	class Transform;
}

namespace HMEngine::Core::Rendering
{
	class Camera
	{
	public:
		static HMEngine::Core::Rendering::Camera& GetInstance();

		/* Getters/Setters/Adders for position */
		inline float GetPositionX() const { return this->_transform->GetPositionX(); }
		inline float GetPositionY() const { return this->_transform->GetPositionY(); }
		inline float GetPositionZ() const { return this->_transform->GetPositionZ(); }
		inline glm::vec3 GetPosition() const { return this->_transform->GetPosition(); }
		inline void SetPositionX(float x) { this->_transform->SetPositionX(x); }
		inline void SetPositionY(float y) { this->_transform->SetPositionY(y); }
		inline void SetPositionZ(float z) { this->_transform->SetPositionZ(z); }
		inline void SetPosition(const glm::vec3& pos) { this->_transform->SetPosition(pos); }
		inline void SetPosition(float x, float y, float z) { this->_transform->SetPosition(x, y, z); }
		inline void AddPositionX(float x) { this->_transform->AddPositionX(x); };
		inline void AddPositionX(float y) { this->_transform->AddPositionY(y); };
		inline void AddPositionX(float z) { this->_transform->AddPositionZ(z); };
		inline void AddPosition(const glm::vec3& pos) { this->_transform->AddPosition(pos); }
		inline void AddPosition(float x, float y, float z) { this->_transform->AddPosition(x, y, z); }

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