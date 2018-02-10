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
		namespace Physics
		{
			class Ray;
		}
		class Transform;
		namespace Rendering
		{
			class Camera
			{
			public:
				static HMEngine::Core::Rendering::Camera& GetInstance();

				void Update();

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

				inline void SetForawrd(const glm::vec3& forward) { this->_forward = forward; }
				inline void SetUp(const glm::vec3& up) { this->_up = up; }
				inline void SetRight(const glm::vec3& right) { this->_right = right; }

				inline glm::vec3 GetForawrd() const { return this->_forward; }
				inline glm::vec3 GetUp() const { return this->_up; }
				inline glm::vec3 GetRight() const { return this->_right; }

				HMEngine::Core::Physics::Ray GetRayFromScreenPoint(const glm::vec2& screenPos);

				inline glm::mat4 GetViewMatrix() const { return this->_viewMatrix; }
				inline glm::mat4 GetMVP() const;
			private:
				Camera();
				Camera(const HMEngine::Core::Rendering::Camera& other) = delete;
				HMEngine::Core::Rendering::Camera& operator=(HMEngine::Core::Rendering::Camera& other) = delete;
				~Camera();

				HMEngine::Core::Transform* _transform;
				glm::vec3 _forward, _right, _up;
				glm::mat4 _viewMatrix = glm::mat4(1);
				const unsigned int& _windowWidth, _windowHeight;
				glm::mat4& _projectionMatrix;

				inline glm::vec2 GetNormalizedCoords(float x, float y) const { return glm::vec2((2.0f * x) / this->_windowWidth - 1.0f, -((2.0f * y) / this->_windowHeight - 1.0f)); }
				inline glm::vec2 GetNormalizedCoords(const glm::vec2& pos) const { return glm::vec2((2.0f * pos.x) / this->_windowWidth - 1.0f, -((2.0f * pos.y) / this->_windowHeight - 1.0f)); }
				glm::vec4 ConvertToEyeCoords(const glm::vec4& coords) const;
				glm::vec3 ConvertToWorldCoords(const glm::vec4& coords) const;
			};
		}
	}
}