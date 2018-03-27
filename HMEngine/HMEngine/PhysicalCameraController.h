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

		class PhysicalCameraController : public HMEngine::Components::Component
		{
		public:
			PhysicalCameraController();
			~PhysicalCameraController();
			PhysicalCameraController(const HMEngine::Components::PhysicalCameraController& other);
			HMEngine::Components::PhysicalCameraController& operator=(const HMEngine::Components::PhysicalCameraController& other);

			inline HMEngine::Components::Component* Clone() override { return new HMEngine::Components::PhysicalCameraController(*this); }

			inline void Activate() { this->_isActive = true; }
			inline void Deactivate() { this->_isActive = false; }

			void UpdateEvent() override;

			inline glm::vec3 GetRight() const { return this->_right; }
			inline glm::vec3 GetForward() const { return this->_forward; }
			inline glm::vec3 GetUp() const { return this->_up; }

			inline float GetVerticalAngle() const { return this->_verticalAngle; }
			inline float GetHorizontalAngle() const { return this->_horizontalAngle; }

		private:
			HMEngine::Core::Rendering::Camera* _camera;
			bool _isActive;
			glm::vec3 _right;
			glm::vec3 _forward;
			glm::vec3 _up;
			float _horizontalAngle;
			float _verticalAngle;
		};
	}
}