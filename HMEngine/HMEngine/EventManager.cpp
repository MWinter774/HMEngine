#include "EventManager.h"
#include "GameEngineObject.h"

std::set<HMEngine::Core::GameEngineObject*> HMEngine::Core::EventManager::_updateOverriders;
std::set<HMEngine::Core::GameEngineObject*> HMEngine::Core::EventManager::_drawOverriders;

void HMEngine::Core::EventManager::UpdateObjects()
{
	for (auto& object : HMEngine::Core::EventManager::_updateOverriders)
	{
		object->UpdateEvent();
	}
}

void HMEngine::Core::EventManager::AddUpdateEventOverrider(HMEngine::Core::GameEngineObject* object)
{
	HMEngine::Core::EventManager::_updateOverriders.insert(object);
}

void HMEngine::Core::EventManager::AddDrawEventOverrider(HMEngine::Core::GameEngineObject* object)
{
	HMEngine::Core::EventManager::_drawOverriders.insert(object);
}