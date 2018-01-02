#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\matrix_transform_2d.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

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

				glm::mat4 GetViewMatrix();
				glm::mat4 GetMVP() const;
			private:
				Camera();
				Camera(const HMEngine::Core::Rendering::Camera& other) = delete;
				HMEngine::Core::Rendering::Camera& operator=(HMEngine::Core::Rendering::Camera& other) = delete;
				~Camera();

				HMEngine::Core::Transform* _transform;
				glm::vec3 _forward, _up;
				glm::mat4 _viewMatrix = glm::mat4(1);
			};
		}
	}
}