#include "PhysicalPlayer.h"
#include "PhysicalCameraController.h"
#include "Transform.h"
#include "BoundingSphere.h"
#include "SDL2.0.7\SDL.h"
#include "Camera.h"
#include "HardwareInputs.h"

HMEngine::PhysicalPlayer::PhysicalPlayer(const std::string& name, float walkingSpeed, float runningSpeed) : GameObject(name),
_controller(new HMEngine::Components::PhysicalCameraController(walkingSpeed, runningSpeed)),
_boundingSphere(new HMEngine::Core::Physics::Colliders::BoundingSphere(1.0f, glm::vec3(0,0,0), 1.5f)),
_camera(&HMEngine::Core::Rendering::Camera::GetInstance())
{
	this->InitializeEvents<PhysicalPlayer>(this);
	this->AddComponent(this->_controller);
	this->AddComponent(this->_boundingSphere);
	this->GetTransform().SetScaleZ(1.5f);
	this->GetTransform().SetRotationX(1.57f);
}

HMEngine::PhysicalPlayer::~PhysicalPlayer()
{
}

HMEngine::PhysicalPlayer::PhysicalPlayer(const HMEngine::PhysicalPlayer& other) : GameObject(other), _controller(other._controller), 
_boundingSphere(other._boundingSphere)
{
	this->InitializeEvents<PhysicalPlayer>(this);
}

HMEngine::PhysicalPlayer& HMEngine::PhysicalPlayer::operator=(const HMEngine::PhysicalPlayer& other)
{
	if (this != &other)
	{
		this->InitializeEvents<PhysicalPlayer>(this);
		HMEngine::Core::GameObject::operator=(other);
		this->_controller = other._controller;
		this->_boundingSphere = other._boundingSphere;
	}

	return *this;
}

void HMEngine::PhysicalPlayer::AttachToGameEngineEvent()
{
	this->InitializeEventObject();
}

void HMEngine::PhysicalPlayer::UpdateEvent()
{
	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_W))
	{
		this->_boundingSphere->ApplyForce(this->_controller->GetForward() *= 200);
	}
	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_A))
	{
		this->_boundingSphere->ApplyForce(this->_controller->GetRight() *= -200);
	}
	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_S))
	{
		this->_boundingSphere->ApplyForce(this->_controller->GetForward() *= -200);
	}
	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_D))
	{
		this->_boundingSphere->ApplyForce(this->_controller->GetRight() *= 200);
	}

	this->_camera->SetPosition(this->GetTransform().GetPosition() += glm::vec3(1, 2, 0));
}