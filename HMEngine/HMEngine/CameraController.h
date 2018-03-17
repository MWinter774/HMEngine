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
		typedef struct
		{
			bool forward;
			bool backward;
			bool right;
			bool left;
		} MovementData;

		class CameraController : public HMEngine::Components::Component
		{
		public:
			CameraController(float walkingSpeed = 3.0f, float runningSpeed = 10.0f);
			~CameraController();
			CameraController(const HMEngine::Components::CameraController& other);
			HMEngine::Components::CameraController& operator=(const HMEngine::Components::CameraController& other);

			void UpdateEvent() override;
			inline HMEngine::Components::Component* Clone() override { return new HMEngine::Components::CameraController(*this); }

			inline void Activate() { this->_isActive = true; }
			inline void Deactivate() { this->_isActive = false; }

			inline const MovementData& GetMovement() { return *this->_movement; }

		private:
			HMEngine::Core::Rendering::Camera* _camera;
			float _horizontalAngle;
			float _verticalAngle;
			float _movementSpeed;
			float _runningSpeed;
			float _walkingSpeed;
			glm::vec3 _right;
			glm::vec3 _forward;
			glm::vec3 _up;
			bool _isActive;
			MovementData* _movement;

			void Move(const glm::vec3& direction, float amount) const;
		};
	}
}