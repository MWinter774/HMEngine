#pragma once
#include "Component.h"
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
		namespace Rendering
		{
			class Camera;
		}
	}
	namespace Components
	{
		class CameraController : public HMEngine::Components::Component
		{
		public:
			CameraController();
			~CameraController();

			void UpdateEvent() override;
			inline HMEngine::Components::Component* Clone() override { return new HMEngine::Components::CameraController(*this); }

		private:
			HMEngine::Core::Rendering::Camera& _camera;
			float _horizontalAngle;
			float _verticalAngle;
			float _movementSpeed;
			glm::vec3 _right;
			glm::vec3 _forward;
			glm::vec3 _up;

			void Move(const glm::vec3& direction, float amount) const;
		};
	}
}