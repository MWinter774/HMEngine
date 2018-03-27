#include "PhysicalPlayer.h"
#include "PhysicalCameraController.h"
#include "Transform.h"
#include "BoundingSphere.h"
#include "SDL2.0.7\SDL.h"
#include "Camera.h"
#include "HardwareInputs.h"
#include "GameSettings.h"
#include "PhysicsEngine.h"

HMEngine::PhysicalPlayer::PhysicalPlayer(const std::string& name, float walkingSpeed, float runningSpeed, float maxJumpHeight) : GameObject(name),
_controller(new HMEngine::Components::PhysicalCameraController()),
_boundingSphere(new HMEngine::Core::Physics::Colliders::BoundingSphere(2.0f, glm::vec3(0, 0, 0), 1.5f)),
_camera(&HMEngine::Core::Rendering::Camera::GetInstance()), _movement(new HMEngine::PhysicalPlayer::MovementData()),
_movementSpeed(walkingSpeed), _walkingSpeed(walkingSpeed), _runningSpeed(runningSpeed), _maxJumpHeight(maxJumpHeight)
{
	this->InitializeEvents<PhysicalPlayer>(this);
	this->AddComponent(this->_controller);
	this->AddComponent(this->_boundingSphere);
	this->GetTransform().SetScaleZ(1.5f);
	this->GetTransform().SetScaleX(1.5f);
	this->GetTransform().SetScaleY(1.5f);

}

HMEngine::PhysicalPlayer::~PhysicalPlayer()
{
	delete this->_movement;
}

HMEngine::PhysicalPlayer::PhysicalPlayer(const HMEngine::PhysicalPlayer& other) : GameObject(other), _controller(other._controller),
_boundingSphere(other._boundingSphere), _camera(other._camera), _movement(new HMEngine::PhysicalPlayer::MovementData(*other._movement)),
_movementSpeed(other._movementSpeed), _walkingSpeed(other._walkingSpeed), _runningSpeed(other._runningSpeed), _maxJumpHeight(other._maxJumpHeight)
{
	this->InitializeEvents<PhysicalPlayer>(this);
}

HMEngine::PhysicalPlayer& HMEngine::PhysicalPlayer::operator=(const HMEngine::PhysicalPlayer& other)
{
	if (this != &other)
	{
		delete this->_movement;

		this->InitializeEvents<PhysicalPlayer>(this);
		HMEngine::Core::GameObject::operator=(other);
		this->_controller = other._controller;
		this->_boundingSphere = other._boundingSphere;
		this->_movement = new HMEngine::PhysicalPlayer::MovementData(*other._movement);
		this->_movementSpeed = other._movementSpeed;
		this->_walkingSpeed = other._walkingSpeed;
		this->_runningSpeed = other._runningSpeed;
		this->_maxJumpHeight = other._maxJumpHeight;
	}

	return *this;
}

void HMEngine::PhysicalPlayer::AttachToGameEngineEvent()
{
	this->InitializeEventObject();
}

void HMEngine::PhysicalPlayer::UpdateEvent()
{
	this->_boundingSphere->GetRigidBody()->setActivationState(1);

	HMEngine::GameSettings::SetIsCursorLocked(!HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_E));
	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_LSHIFT))
	{
		this->_movementSpeed = this->_runningSpeed;
	}
	glm::vec3 force;
	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_W))
	{
		force += this->_controller->GetForward() *= this->_movementSpeed;
		this->_movement->forward = true;
	}
	else
	{
		this->_movement->forward = false;
	}

	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_A))
	{
		force += this->_controller->GetRight() *= -this->_movementSpeed;
		this->_movement->left = true;
	}
	else
	{
		this->_movement->left = false;
	}

	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_S))
	{
		force += this->_controller->GetForward() *= -this->_movementSpeed;
		this->_movement->backward = true;
	}
	else
	{
		this->_movement->backward = false;
	}

	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_D))
	{
		force += this->_controller->GetRight() *= this->_movementSpeed;
		this->_movement->right = true;
	}
	else
	{
		this->_movement->right = false;
	}
	this->_movementSpeed = this->_walkingSpeed;
	force.y = 0;

	this->_boundingSphere->GetRigidBody()->setLinearVelocity(btVector3(force.x * 20.0f, this->_boundingSphere->GetRigidBody()->getLinearVelocity().y(),
		force.z * 20.0f));

	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_SPACE))
	{
		auto camPos = this->GetTransform().GetPosition();
		btVector3 btFrom(camPos.x, camPos.y, camPos.z);
		btVector3 btTo(camPos.x, -5000.0f, camPos.z);
		btCollisionWorld::ClosestRayResultCallback res(btFrom, btTo);
		HMEngine::Core::Physics::PhysicsEngine::GetBulletData().dynamicsWorld->rayTest(btFrom, btTo, res);
		if (res.hasHit() && res.m_closestHitFraction <= 0.0008f)
			this->_boundingSphere->GetRigidBody()->applyCentralImpulse(btVector3(0, this->_maxJumpHeight / 4.0f, 0));
	}

	this->_camera->SetPosition(this->GetTransform().GetPosition() += glm::vec3(0, 2, 0));
}