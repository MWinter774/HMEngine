#pragma once
#include "PhysicalPlayer.h"
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

	void MouseButtonDownEvent(const unsigned int& mouseButton) override;

private:
	HMEngine::PhysicalPlayer* _player;
	HMEngine::Core::GameObject* _floor;
	EnemyBot* _bot;
	HMEngine::UI::Image* _crosshair;

	void Restart();
};

