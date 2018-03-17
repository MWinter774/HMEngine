#include "BrainComponent.h"
#include "Player.h"

HMEngine::Components::BrainComponent::BrainComponent(const HMEngine::Player& player) : HMEngine::Components::Component(), _neuralNetwork({ 4, 20, 20, 1 }),
_player(&player), _playerMovement(&player.GetCameraController()->GetMovement())
{
	this->InitializeEvents<BrainComponent>(this);
}

HMEngine::Components::BrainComponent::~BrainComponent()
{
}

HMEngine::Components::BrainComponent::BrainComponent(const HMEngine::Components::BrainComponent& other) : HMEngine::Components::Component(other), 
_neuralNetwork(other._neuralNetwork), _player(other._player), _playerMovement(&other._player->GetCameraController()->GetMovement())
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
		this->_playerMovement = &this->_player->GetCameraController()->GetMovement();
	}

	return *this;
}

void HMEngine::Components::BrainComponent::UpdateEvent()
{
	if (this->_playerMovement->forward)
	{
		std::cout << "Player is going forward" << std::endl;
	}
	if (this->_playerMovement->backward)
	{
		std::cout << "Player is going backward" << std::endl;
	}
	if (this->_playerMovement->right)
	{
		std::cout << "Player is going right" << std::endl;
	}
	if (this->_playerMovement->left)
	{
		std::cout << "Player is going left" << std::endl;
	}
}