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
#include "EnemyBot.h"

HMEngine::Components::BrainComponent::BrainComponent(const HMEngine::PhysicalPlayer& player) : HMEngine::Components::Component(), _gnn(6, { 8, 20, 20, 5 }),
_player(&player), _playerMovement(&player.GetMovement()), _currentPlayerMovement(4), _futurePlayerMovement(4), _timer(0), _rightAVG(0), _forwardAVG(0),
_count(0), _gnnFilePath(), _jumpAVG(0)
{
	this->InitializeEvents<BrainComponent>(this);
}

HMEngine::Components::BrainComponent::BrainComponent(const HMEngine::PhysicalPlayer & player, const std::string & gnnFilePath) :
	HMEngine::Components::Component(), _gnn(gnnFilePath), _player(&player), _playerMovement(&player.GetMovement()), _currentPlayerMovement(4),
	_futurePlayerMovement(4), _timer(0), _rightAVG(0), _forwardAVG(0), _count(0), _gnnFilePath(gnnFilePath), _jumpAVG(0)
{
	this->InitializeEvents<BrainComponent>(this);
}

HMEngine::Components::BrainComponent::~BrainComponent()
{
	if (!this->_gnnFilePath.empty())
	{
		this->_gnn.Save(this->_gnnFilePath);
	}
}

HMEngine::Components::BrainComponent::BrainComponent(const HMEngine::Components::BrainComponent& other) : HMEngine::Components::Component(other),
_gnn(other._gnn), _player(other._player), _playerMovement(&other._player->GetMovement()), _currentPlayerMovement(4), _futurePlayerMovement(4)
{
	this->InitializeEvents<BrainComponent>(this);
}

HMEngine::Components::BrainComponent& HMEngine::Components::BrainComponent::operator=(const HMEngine::Components::BrainComponent& other)
{
	if (this != &other)
	{
		this->InitializeEvents<BrainComponent>(this);
		this->_gnn = other._gnn;
		this->_player = other._player;
		this->_playerMovement = &this->_player->GetMovement();
		this->_currentPlayerMovement = std::vector<float>(4);
		this->_futurePlayerMovement = std::vector<float>(4);
	}

	return *this;
}

void HMEngine::Components::BrainComponent::UpdateEvent()
{
	this->_timer += (1 / 60.0f);
	this->FeedForward();
	this->_count++;

	std::vector<float> outputs = this->_gnn.GetResults();

	float right = (outputs[0] * 10000.0f) - int(outputs[0] * 10000.0f);
	float left = (outputs[1] * 10000.0f) - int(outputs[1] * 10000.0f);
	float forward = (outputs[2] * 10000.0f) - int(outputs[2] * 10000.0f);
	float backward = (outputs[3] * 10000.0f) - int(outputs[3] * 10000.0f);
	float jump = (outputs[4] * 10000.0f) - int(outputs[4] * 10000.0f);
	float speed = 0.5f;
	this->_rightAVG += right; //temp
	this->_leftAVG += left; //temp
	this->_forwardAVG += forward; //temp
	this->_backwardAVG += backward; //temp
	this->_jumpAVG += jump;

	glm::vec3 translate;
	if (right > 0.9f)
		translate.x += speed;
	else if (left > 0.9f)
		translate.x -= speed;
	if (forward > 0.9f)
		translate.z += speed;
	else if (backward > 0.9f)
		translate.z -= speed;
	if (jump > 0.9f)
		this->_parent->Jump();

	this->_parent->AddPosition(translate);
}

void HMEngine::Components::BrainComponent::AttachToGameObjectEvent()
{
	this->_parent = dynamic_cast<EnemyBot*>(this->_parentObject);
}

void HMEngine::Components::BrainComponent::Lost()
{
	float rightAVG = this->_rightAVG / this->_count;
	float leftAVG = this->_leftAVG / this->_count;
	float forwardAVG = this->_forwardAVG / this->_count;
	float backwardAVG = this->_backwardAVG / this->_count;
	float jumpAVG = this->_jumpAVG / this->_count;
	this->_count = 0;
	this->_rightAVG = 0;
	this->_leftAVG = 0;
	this->_forwardAVG = 0;
	this->_backwardAVG = 0;
	this->_jumpAVG = 0;
	std::cout << "**************" << std::endl;
	std::cout << "Right Average: " << rightAVG << std::endl;
	std::cout << "Left Average: " << leftAVG << std::endl;
	std::cout << "Forward Average: " << forwardAVG << std::endl;
	std::cout << "Backward Average: " << backwardAVG << std::endl;
	std::cout << "Jump Average: " << jumpAVG << std::endl;
	std::cout << "**************" << std::endl;

	this->_gnn.SetFitness(this->_timer);
	this->_timer = 0.0f;
	this->_gnn.Step();
}

void HMEngine::Components::BrainComponent::FeedForward()
{
	std::vector<float> input;

	/* Adds enemyPosition */
	auto enemyPosition = this->_player->GetTransform().GetPosition();
	input.push_back(enemyPosition.x);
	input.push_back(enemyPosition.y);
	input.push_back(enemyPosition.z);

	/* Adds enemyInSight */
	float enemyInSight = this->_parent->Shoot();
	input.push_back(enemyInSight);

	/* Adds isEnemyShooting */
	float isEnemyShooting = HMEngine::Core::Hardware::HardwareInputs::IsMouseButtonDown(SDL_BUTTON_LEFT);
	input.push_back(isEnemyShooting);

	/* Adds myPosition */
	auto myPosition = this->_parent->GetTransform().GetPosition();
	input.push_back(myPosition.x);
	input.push_back(myPosition.y);
	input.push_back(myPosition.z);

	this->_gnn.FeedForward(input);
}
