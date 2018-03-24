#pragma once
#include "Component.h"
#include "glm\glm.hpp"

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

		class PhysicalCameraController : public HMEngine::Components::Component
		{
		public:
			PhysicalCameraController(float walkingSpeed = 3.0f, float runningSpeed = 10.0f);
			~PhysicalCameraController();
			PhysicalCameraController(const HMEngine::Components::PhysicalCameraController& other);
			HMEngine::Components::PhysicalCameraController& operator=(const HMEngine::Components::PhysicalCameraController& other);

			inline HMEngine::Components::Component* Clone() override { return new HMEngine::Components::PhysicalCameraController(*this); }

			inline void Activate() { this->_isActive = true; }
			inline void Deactivate() { this->_isActive = false; }

			inline const MovementData& GetMovement() { return *this->_movement; }

			void UpdateEvent() override;

			inline glm::vec3 GetRight() const { return this->_right; }
			inline glm::vec3 GetForward() const { return this->_forward; }
			inline glm::vec3 GetUp() const { return this->_up; }

		private:
			HMEngine::Core::Rendering::Camera* _camera;
			bool _isActive;
			float _movementSpeed;
			float _runningSpeed;
			float _walkingSpeed;
			MovementData* _movement;
			glm::vec3 _right;
			glm::vec3 _forward;
			glm::vec3 _up;
			float _horizontalAngle;
			float _verticalAngle;

			void Move(const glm::vec3& direction, float amount) const;
		};
	}
}