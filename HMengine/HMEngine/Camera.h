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
				float GetPositionX() const;
				float GetPositionY() const;
				float GetPositionZ() const;
				glm::vec3 GetPosition() const;
				void SetPositionX(float x);
				void SetPositionY(float y);
				void SetPositionZ(float z);
				void SetPosition(const glm::vec3& pos);
				void SetPosition(float x, float y, float z);
				void AddPositionX(float x);
				void AddPositionY(float y);
				void AddPositionZ(float z);
				void AddPosition(const glm::vec3& pos);
				void AddPosition(float x, float y, float z);

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