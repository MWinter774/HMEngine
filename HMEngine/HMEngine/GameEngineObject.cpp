#include "GameEngineObject.h"

HMEngine::Core::GameEngineObject::GameEngineObject() : _isAttachedToGameEngine(false), _gameEngine(nullptr), _hasUpdateEvent(false), _hasDrawEvent(false)
{
}

HMEngine::Core::GameEngineObject::~GameEngineObject()
{
}

void HMEngine::Core::GameEngineObject::InitializeGameEngineObject()
{
	if (this->_hasUpdateEvent)
		HMEngine::Core::EventManager::AddUpdateEventOverrider(this->_object);
	if (this->_hasDrawEvent)
		HMEngine::Core::EventManager::AddDrawEventOverrider(this->_object);
}

void HMEngine::Core::GameEngineObject::AttachToGameEngine(HMEngine::GameEngine& gameEngine)
{
	this->_gameEngine = &gameEngine;
	this->_isAttachedToGameEngine = true;

	this->AttachToGameEngineEvent(gameEngine);
}
