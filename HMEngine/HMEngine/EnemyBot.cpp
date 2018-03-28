#include "EnemyBot.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "BoundingSphere.h"
#include "BrainComponent.h"
#include "Billboard.h"
#include "ProgressBar.h"
#include "GameEngine.h"

EnemyBot::EnemyBot(const std::string& name, const glm::vec3& position, HMEngine::PhysicalPlayer* player) : HMEngine::Core::GameObject(name),
_player(player)
{
	this->InitializeEvents<EnemyBot>(this);
	this->GetTransform().SetPosition(position);
	this->GetTransform().SetScaleZ(1.5f);
	this->GetTransform().SetRotationX(1.57f);
}

EnemyBot::~EnemyBot()
{
}

int asd = 0;
void EnemyBot::UpdateEvent()
{
	auto newPos = this->GetTransform().GetPosition() += glm::vec3(0, 3, 0);
	this->_health->SetPosition(newPos);
	for (auto& child : this->_health->GetChilds())
		child->SetPosition(newPos);
	asd++;
}

void EnemyBot::AttachToGameEngineEvent()
{
	this->_mesh = new HMEngine::Components::MeshRenderer("./resources/objects/capsule.obj", "./resources/textures/mud.png");
	this->_brain = new HMEngine::Components::BrainComponent(*this->_player);
	this->_collider = new HMEngine::Core::Physics::Colliders::BoundingSphere(10.0f);
	this->_health = new HMEngine::UI::ProgressBar(this->GetName() + "_health", glm::vec2(), glm::vec2(5, 1), "./resources/UITextures/progressBarBackground.png",
		"./resources/UITextures/progressBarBarTexture.png", 100);
	this->_healthBar = new HMEngine::UI::Billboard(this->GetName() + "_healthBar", this->GetTransform().GetPosition() += glm::vec3(0, 2, 0), this->_health);
	this->AddComponent(this->_mesh);
	this->AddComponent(this->_brain);
	this->AddComponent(this->_collider);
	this->GetGameEngine().AddUI(this->_healthBar);
	this->InitializeEventObject();
}
