#pragma once
#include <string>
#include "GameObject.h"
#include "EventObject.h"

namespace HMEngine
{
	namespace Components
	{
		class PhysicalCameraController;
	}
	namespace Core
	{
		namespace Rendering
		{
			class Camera;
		}
		namespace Physics
		{
			namespace Colliders
			{
				class BoundingSphere;
			}
		}
	}

	class PhysicalPlayer : public HMEngine::Core::GameObject, public HMEngine::Core::EventObject
	{
	public:
		PhysicalPlayer(const std::string& name, float walkingSpeed, float runningSpeed);
		~PhysicalPlayer();
		PhysicalPlayer(const HMEngine::PhysicalPlayer& other);
		HMEngine::PhysicalPlayer& operator=(const HMEngine::PhysicalPlayer& other);

		inline HMEngine::Core::GameObject* Clone() const override { return new HMEngine::PhysicalPlayer(*this); }

		inline HMEngine::Components::PhysicalCameraController* GetCameraController() const { return this->_controller; }

		void AttachToGameEngineEvent() override;

		void UpdateEvent() override;

	private:
		HMEngine::Core::Rendering::Camera* _camera;
		HMEngine::Components::PhysicalCameraController* _controller;
		HMEngine::Core::Physics::Colliders::BoundingSphere* _boundingSphere;
	};
}