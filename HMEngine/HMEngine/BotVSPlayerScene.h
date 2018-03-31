#pragma once
//#include "PhysicalPlayer.h"
#include "MainPlayer.h"
#include "GameObject.h"
#include "EnemyBot.h"
#include "Image.h"
#include "GameEngine.h"
#include "EventObject.h"

class BotVSPlayerScene : public HMEngine::Core::EventObject
{
public:
	BotVSPlayerScene();
	~BotVSPlayerScene();
	BotVSPlayerScene(const BotVSPlayerScene& other) = delete;
	BotVSPlayerScene& operator=(const BotVSPlayerScene& other) = delete;

	void AddToGameEngine(HMEngine::GameEngine& gameEngine);

	void UpdateEvent() override;

private:
	MainPlayer* _player;
	HMEngine::Core::GameObject* _floor;
	EnemyBot* _bot;
	HMEngine::UI::Image* _crosshair;
	std::vector<HMEngine::Core::GameObject*> _ammoPacks;

	void Restart();
	void ShootEvent(HMEngine::Core::Physics::RaycastInfo& info);

	void InitAmmoPacks();
};

