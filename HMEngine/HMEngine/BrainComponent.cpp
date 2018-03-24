#include "BrainComponent.h"
#include "PhysicalPlayer.h"
#include "Transform.h"
#include "Camera.h"
#include "glm\gtc\quaternion.hpp"
#include <math.h>
#include "PhysicsEngine.h"
#include "RaycastInfo.h"
#include "HardwareInputs.h"
#include "GameObject.h"

HMEngine::Components::BrainComponent::BrainComponent(const HMEngine::PhysicalPlayer& player) : HMEngine::Components::Component(), _neuralNetwork({ 4, 20, 20, 4 }),
_player(&player), _playerMovement(&player.GetMovement()), _currentPlayerMovement(4), _futurePlayerMovement(4)
{
	this->InitializeEvents<BrainComponent>(this);
}

HMEngine::Components::BrainComponent::~BrainComponent()
{
}

HMEngine::Components::BrainComponent::BrainComponent(const HMEngine::Components::BrainComponent& other) : HMEngine::Components::Component(other),
_neuralNetwork(other._neuralNetwork), _player(other._player), _playerMovement(&other._player->GetMovement()),
_currentPlayerMovement(4), _futurePlayerMovement(4)
{
	this->InitializeEvents<BrainComponent>(this);
}

HMEngine::Components::BrainComponent& HMEngine::Components::BrainComponent::operator=(const HMEngine::Components::BrainComponent& other)
{
	if (this != &other)
	{
		this->InitializeEvents<BrainComponent>(this);
		this->_neuralNetwork = other._neuralNetwork;
		this->_player = other._player;
		this->_playerMovement = &this->_player->GetMovement();
		this->_currentPlayerMovement = std::vector<float>(4);
		this->_futurePlayerMovement = std::vector<float>(4);
	}

	return *this;
}

void HMEngine::Components::BrainComponent::UpdateEvent()
{
	/*this->ConstructCurrentPlayerMovement();

	if (this->_currentPlayerMovement != this->_futurePlayerMovement)
	{
		this->_neuralNetwork.BackProp(this->_currentPlayerMovement);
	}

	this->_neuralNetwork.FeedForward(this->_currentPlayerMovement);

	this->_futurePlayerMovement = this->_neuralNetwork.GetResults();

	if (this->_futurePlayerMovement[0] > 0.9f)
	{
		this->_parentObject->GetTransform().AddPositionZ(0.1f);
		std::cout << "forward" << std::endl;
	}
	if (this->_futurePlayerMovement[1] > 0.9f)
	{
		this->_parentObject->GetTransform().AddPositionZ(-0.1f);
		std::cout << "backwards" << std::endl;
	}
	if (this->_futurePlayerMovement[2] > 0.9f)
	{
		this->_parentObject->GetTransform().AddPositionX(-0.1f);
		std::cout << "right" << std::endl;
	}
	if (this->_futurePlayerMovement[3] > 0.9f)
	{
		this->_parentObject->GetTransform().AddPositionX(0.1f);
		std::cout << "left" << std::endl;
	}*/

	//auto ray2 = HMEngine::Core::Rendering::Camera::GetInstance().GetRayFromScreenPoint(HMEngine::Core::Hardware::HardwareInputs::GetCursorPos());
	//HMEngine::Core::Physics::RaycastInfo f = HMEngine::Core::Physics::PhysicsEngine::Raycast(ray2);

	/*auto f = HMEngine::Core::Physics::PhysicsEngine::Raycast(this->_parentObject->GetTransform().GetPosition(),
		 this->_player->GetTransform().GetPosition() - this->_parentObject->GetTransform().GetPosition(), 5);

	if (f.HasObject(*this))

		auto ray = HMEngine::Core::Physics::PhysicsEngine::Raycast(this->_parentObject->GetTransform().GetPosition(), this->_player->GetTransform().GetPosition(), 50);

	{
		std::cout << "1";
	}*/

	if (HMEngine::Core::Hardware::HardwareInputs::IsMouseButtonDown(SDL_BUTTON_LEFT))
	{
		auto ray = HMEngine::Core::Rendering::Camera::GetInstance().GetRayFromScreenPoint(HMEngine::Core::Hardware::HardwareInputs::GetCursorPos());
		auto k = HMEngine::Core::Physics::PhysicsEngine::Raycast(ray);
		if (k)
			std::cout << k.hits.begin().operator*().second->GetName() << std::endl;
	}
	//this->_parentObject->GetTransform().LookAt(HMEngine::Core::Rendering::Camera::GetInstance().GetPosition());
	//this->_parentObject->GetTransform().AddPositionX(0.01f);
}