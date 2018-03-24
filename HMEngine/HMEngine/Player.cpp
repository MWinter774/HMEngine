#include "Player.h"
#include "MeshRenderer.h"
#include "CameraController.h"
#include "Transform.h"

HMEngine::Player::Player(const std::string& playerName, float walkingSpeed, float runningSpeed) : GameObject(playerName), _cameraController(new HMEngine::Components::CameraController(walkingSpeed, runningSpeed))
{
	this->AddComponent(this->_cameraController);
}

HMEngine::Player::~Player()
{
}

HMEngine::Player::Player(const HMEngine::Player& other) : GameObject(other), _cameraController(new HMEngine::Components::CameraController(*other._cameraController))
{
}

HMEngine::Player& HMEngine::Player::operator=(const HMEngine::Player& other)
{
	if (this != &other)
	{
		delete this->_cameraController;
		this->_cameraController = new HMEngine::Components::CameraController(*other._cameraController);
	}

	return *this;
}
