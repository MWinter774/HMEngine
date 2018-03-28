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

BotVSPlayerScene::BotVSPlayerScene()
{
	this->_player = new HMEngine::PhysicalPlayer("player", 1.0f, 2.0f);
	this->_player->GetTransform().AddPositionY(0.1f);

	this->_floor = new HMEngine::Core::GameObject("floor");
	this->_floor->GetTransform().SetScaleX(10.0f);
	this->_floor->GetTransform().SetScaleZ(10.0f);
	this->_floor->AddComponent(HMEngine::Core::Physics::Colliders::BoundingPlane(0.0f));
	this->_floor->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/plane.obj", "./resources/textures/VeryNice.png"));

	this->_bot = new EnemyBot("bot1", glm::vec3(5, 3, 0), this->_player);

	this->_crosshair = new HMEngine::UI::Image("crosshair", "./resources/UITextures/crosshair.png", HMEngine::GameSettings::GetScreenCenter(), { 25, 25 });

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

	gameEngine.SetAmbientLight(1, 1, 1);

	this->InitializeEventObject();
}

void BotVSPlayerScene::MouseButtonDownEvent(const unsigned int& mouseButton)
{
	if (mouseButton == SDL_BUTTON_LEFT)
	{
		HMEngine::Core::Physics::Ray ray = HMEngine::Core::Rendering::Camera::GetInstance().GetRayFromScreenPoint(HMEngine::GameSettings::GetScreenCenter());
		auto k = HMEngine::Core::Physics::PhysicsEngine::Raycast(ray);
		if (k)
		{
			if (k.hits.begin().operator*().second == this->_bot)
			{
				if (this->_bot->GotHit(10.0f))
				{
					this->Restart();
				}
			}
		}
	}
}

void BotVSPlayerScene::Restart()
{
	this->_bot->SetPosition(glm::vec3(5, 3, 0));
	this->_bot->SetHealth(100.0f);
	this->_player->SetPosition(glm::vec3(0, 0.1f, 0));
}
