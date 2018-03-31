#include "BotVSPlayerScene.h"
#include "Transform.h"
#include "BoundingPlane.h"
#include "BoundingSphere.h"
#include "MeshRenderer.h"
#include "GameSettings.h"
#include "Ray.h"
#include "PhysicsEngine.h"
#include "RaycastInfo.h"
#include "Camera.h"
#include <string>
#include <thread>
#include <chrono>

BotVSPlayerScene::BotVSPlayerScene()
{
	this->_player = new MainPlayer("player", 1.0f, 2.0f);
	this->_player->GetTransform().AddPositionY(0.1f);
	this->_player->_shootEvent.push_back(std::bind(&BotVSPlayerScene::ShootEvent, this, std::placeholders::_1));

	this->_floor = new HMEngine::Core::GameObject("floor");
	this->_floor->GetTransform().SetScaleX(10.0f);
	this->_floor->GetTransform().SetScaleZ(10.0f);
	this->_floor->AddComponent(HMEngine::Core::Physics::Colliders::BoundingPlane(0.0f));
	this->_floor->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/plane.obj", "./resources/textures/VeryNice.png"));

	this->_bot = new EnemyBot("bot1", glm::vec3(5, 3, 0), this->_player, "./resources/neuralNetworks/enemyBot.gnn");
	//this->_bot = new EnemyBot("bot1", glm::vec3(5, 3, 0), this->_player);

	this->_crosshair = new HMEngine::UI::Image("crosshair", "./resources/UITextures/crosshair.png", HMEngine::GameSettings::GetScreenCenter(), { 25, 25 });

	this->InitAmmoPacks();

	this->InitializeEvents<BotVSPlayerScene>(this);
}

BotVSPlayerScene::~BotVSPlayerScene()
{
}

void BotVSPlayerScene::AddToGameEngine(HMEngine::GameEngine& gameEngine)
{
	gameEngine.AddGameObject(this->_floor);
	gameEngine.AddGameObject(this->_player);
	gameEngine.AddGameObject(this->_bot);
	gameEngine.AddUI(this->_crosshair);
	for (auto& ammoPack : this->_ammoPacks)
		gameEngine.AddGameObject(ammoPack);

	gameEngine.SetAmbientLight(1, 1, 1);
	//gameEngine.UnlockCursor();
	//gameEngine.SetMouseVisible(true);

	this->InitializeEventObject();
}

void BotVSPlayerScene::UpdateEvent()
{
	if (this->_bot->GetTransform().GetPositionY() < -5.0f)
	{
		this->_bot->Lost();
		this->Restart();
	}
}

void BotVSPlayerScene::Restart()
{
	this->_bot->SetPosition(glm::vec3(5, 3, 0));
	this->_bot->SetHealth(100.0f);
	this->_player->SetPosition(glm::vec3(0, 0.1f, 0));
	this->_player->SetAmmo(30);
}

void BotVSPlayerScene::ShootEvent(HMEngine::Core::Physics::RaycastInfo& info)
{
	if (info.hits.begin().operator*().second == this->_bot)
	{
		if (this->_bot->GotHit(10.0f))
		{
			this->_bot->Lost();
			this->Restart();
		}
	}
}

void BotVSPlayerScene::InitAmmoPacks()
{
	auto collideEvent = [](HMEngine::Core::GameObject* a, HMEngine::Core::GameObject* b)
	{
		if (auto player = dynamic_cast<MainPlayer*>(b))
		{
			if (a->GetColor().x != 0.2f) //checks if the bullet pack is active
			{
				player->SetAmmo(30);
				a->SetColor(glm::vec3(0.2f, 0.2f, 0.2f));
				std::thread reactivate([](HMEngine::Core::GameObject* a) 
				{
					std::this_thread::sleep_for(std::chrono::seconds(5));
					a->SetColor(glm::vec3(1.0f)); 
				}, a);
				reactivate.detach();
			}
		}
	};
	HMEngine::Core::GameObject* ammo;

	ammo = new HMEngine::Core::GameObject("ammoPack0");
	ammo->GetTransform().AddPositionY(3.0f);
	ammo->GetTransform().AddPositionX(50.0f);
	ammo->GetTransform().AddPositionZ(50.0f);
	ammo->GetTransform().SetRotationZ(1.57f);
	ammo->GetTransform().SetScale(0.02f, 0.02f, 0.02f);
	ammo->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/bullet.obj", "./resources/textures/brass.png"));
	ammo->AddComponent(HMEngine::Core::Physics::Colliders::BoundingPlane(0.0f));
	ammo->_collideEvent.push_back(collideEvent);
	this->_ammoPacks.push_back(ammo);

	ammo = new HMEngine::Core::GameObject("ammoPack1");
	ammo->GetTransform().AddPositionY(3.0f);
	ammo->GetTransform().AddPositionX(-50.0f);
	ammo->GetTransform().AddPositionZ(50.0f);
	ammo->GetTransform().SetRotationZ(1.57f);
	ammo->GetTransform().SetScale(0.02f, 0.02f, 0.02f);
	ammo->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/bullet.obj", "./resources/textures/brass.png"));
	ammo->AddComponent(HMEngine::Core::Physics::Colliders::BoundingSphere(0.0f));
	ammo->_collideEvent.push_back(collideEvent);
	this->_ammoPacks.push_back(ammo);

	ammo = new HMEngine::Core::GameObject("ammoPack2");
	ammo->GetTransform().AddPositionY(3.0f);
	ammo->GetTransform().AddPositionX(50.0f);
	ammo->GetTransform().AddPositionZ(-50.0f);
	ammo->GetTransform().SetRotationZ(1.57f);
	ammo->GetTransform().SetScale(0.02f, 0.02f, 0.02f);
	ammo->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/bullet.obj", "./resources/textures/brass.png"));
	ammo->AddComponent(HMEngine::Core::Physics::Colliders::BoundingSphere(0.0f));
	ammo->_collideEvent.push_back(collideEvent);
	this->_ammoPacks.push_back(ammo);

	ammo = new HMEngine::Core::GameObject("ammoPack3");
	ammo->GetTransform().AddPositionY(3.0f);
	ammo->GetTransform().AddPositionX(-50.0f);
	ammo->GetTransform().AddPositionZ(-50.0f);
	ammo->GetTransform().SetRotationZ(1.57f);
	ammo->GetTransform().SetScale(0.02f, 0.02f, 0.02f);
	ammo->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/bullet.obj", "./resources/textures/brass.png"));
	ammo->AddComponent(HMEngine::Core::Physics::Colliders::BoundingSphere(0.0f));
	ammo->_collideEvent.push_back(collideEvent);
	this->_ammoPacks.push_back(ammo);
}
