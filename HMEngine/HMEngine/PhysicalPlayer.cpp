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
_boundingSphere(new HMEngine::Core::Physics::Colliders::BoundingSphere(2.0f, glm::vec3(0, 0.5f, 0), 2.0f)),
_camera(&HMEngine::Core::Rendering::Camera::GetInstance()), _movement(new HMEngine::PhysicalPlayer::MovementData()),
_movementSpeed(walkingSpeed), _walkingSpeed(walkingSpeed), _runningSpeed(runningSpeed), _maxJumpHeight(maxJumpHeight)
{
	this->InitializeEvents<PhysicalPlayer>(this);
	this->AddComponent(this->_controller);
	this->AddComponent(this->_boundingSphere);
	//this->GetTransform().SetScaleZ(1.5f);
	//this->GetTransform().SetScaleX(1.5f);
	//this->GetTransform().SetScaleY(1.5f);

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

void HMEngine::PhysicalPlayer::SetPosition(const glm::vec3& newPosition)
{
	this->_camera->SetPosition(newPosition);
	this->_boundingSphere->SetPosition(newPosition);
	this->GetTransform().SetPosition(newPosition);
}

void HMEngine::PhysicalPlayer::UpdateEvent()
{
	this->_boundingSphere->GetRigidBody()->setActivationState(1);

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
	force.y = this->_boundingSphere->GetRigidBody()->getLinearVelocity().y();

	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_SPACE))
	{
		auto camPos = this->GetTransform().GetPosition();
		btVector3 btFrom(camPos.x, camPos.y, camPos.z);
		btVector3 btTo(camPos.x, -5000.0f, camPos.z);
		btCollisionWorld::ClosestRayResultCallback res(btFrom, btTo);
		HMEngine::Core::Physics::PhysicsEngine::GetBulletData().dynamicsWorld->rayTest(btFrom, btTo, res);
		if (res.hasHit() && res.m_closestHitFraction <= 0.0008f)
			force.y += this->_maxJumpHeight / 10.0f;
	}

	auto pos = this->_boundingSphere->GetRigidBody()->getWorldTransform().getOrigin();
	pos.setY(RoundNumber(pos.getY()));
	this->_boundingSphere->GetRigidBody()->getWorldTransform().setOrigin(pos);
	auto gPos = glm::vec3(pos.x(), pos.y(), pos.z());
	this->_camera->SetPosition(gPos + glm::vec3(0, 2, 0));

	this->_boundingSphere->GetRigidBody()->setLinearVelocity(btVector3(force.x * 20.0f, force.y,
		force.z * 20.0f));

	for (auto& updateEvent : this->_updateEvents)
		updateEvent();
}

float HMEngine::PhysicalPlayer::RoundNumber(float x)
{
	float decimal = abs(x - int(x));
	unsigned int number = abs(int(x));
	int firstDigit = int(decimal * 10);
	int secondDigit = int(decimal * 100) - firstDigit * 10;
	int thirdDigit = int(decimal * 1000) - secondDigit * 10 - firstDigit * 100;
	//if (thirdDigit >= 5.0f)
	//{
	//	//round up
	//	secondDigit++;
	//	thirdDigit = 0;
	//	if (secondDigit >= 10.0f)
	//	{
	//		firstDigit++;
	//		if (firstDigit >= 10.0f)
	//		{
	//			firstDigit = 0;
	//			number++;
	//		}
	//	}
	//}
	if (secondDigit >= 7)
	{
		firstDigit++;
		if (firstDigit >= 10)
		{
			number++;
			firstDigit = 0;
		}
	}
	secondDigit = 0;
	int factor = x > 0.0f ? 1 : -1;

	return (number + (firstDigit / 10.0f) + (secondDigit / 100.0f)) * factor;
}
