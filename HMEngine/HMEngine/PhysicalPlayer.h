#pragma once
#include <string>
#include "GameObject.h"
#include "EventObject.h"
#include "glm\glm.hpp"

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
		typedef struct
		{
			bool forward;
			bool backward;
			bool right;
			bool left;
		} MovementData;

		PhysicalPlayer(const std::string& name, float walkingSpeed = 5.0f, float runningSpeed = 10.0f, float maxJumpHeight = 5.0f);
		~PhysicalPlayer();
		PhysicalPlayer(const HMEngine::PhysicalPlayer& other);
		HMEngine::PhysicalPlayer& operator=(const HMEngine::PhysicalPlayer& other);

		inline HMEngine::Core::GameObject* Clone() const override { return new HMEngine::PhysicalPlayer(*this); }

		void AttachToGameEngineEvent() override;

		inline const MovementData& GetMovement() const { return *this->_movement; }

		void UpdateEvent() override;

	private:
		HMEngine::Core::Rendering::Camera* _camera;
		HMEngine::Components::PhysicalCameraController* _controller;
		HMEngine::Core::Physics::Colliders::BoundingSphere* _boundingSphere;
		MovementData* _movement;
		float _movementSpeed;
		float _runningSpeed;
		float _walkingSpeed;
		float _maxJumpHeight;
		glm::vec3 _prevLocation;
		float _minY;
		bool _canJump;
	};
}