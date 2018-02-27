#include "EventManager.h"
#include "EventObject.h"

std::set<HMEngine::Core::EventObject*> HMEngine::Core::EventManager::_updateEventOverriders;
std::set<HMEngine::Core::EventObject*> HMEngine::Core::EventManager::_keyDownEventOverriders;
std::set<HMEngine::Core::EventObject*> HMEngine::Core::EventManager::_keyTappedEventOverriders;
std::set<HMEngine::Core::EventObject*> HMEngine::Core::EventManager::_keyUpEventOverriders;
std::set<HMEngine::Core::EventObject*> HMEngine::Core::EventManager::_mouseButtonDownEventOverriders;
std::set<HMEngine::Core::EventObject*> HMEngine::Core::EventManager::_mouseButtonTappedEventOverriders;
std::set<HMEngine::Core::EventObject*> HMEngine::Core::EventManager::_mouseButtonUpEventOverriders;

void HMEngine::Core::EventManager::UpdateObjects()
{
	for (auto& object : HMEngine::Core::EventManager::_updateEventOverriders)
	{
		object->UpdateEvent();
	}
}

void HMEngine::Core::EventManager::KeyDownEvent(const unsigned int& keyCode)
{
	for (auto& object : HMEngine::Core::EventManager::_keyDownEventOverriders)
	{
		object->KeyDownEvent(keyCode);
	}
}

void HMEngine::Core::EventManager::KeyTappedEvent(const unsigned int& keyCode)
{
	for (auto& object : HMEngine::Core::EventManager::_keyTappedEventOverriders)
	{
		object->KeyTappedEvent(keyCode);
	}
}

void HMEngine::Core::EventManager::KeyUpEvent(const unsigned int& keyCode)
{
	for (auto& object : HMEngine::Core::EventManager::_keyUpEventOverriders)
	{
		object->KeyUpEvent(keyCode);
	}
}

void HMEngine::Core::EventManager::MouseButtonDownEvent(const unsigned int& keyCode)
{
	for (auto& object : HMEngine::Core::EventManager::_mouseButtonDownEventOverriders)
	{
		object->MouseButtonDownEvent(keyCode);
	}
}

void HMEngine::Core::EventManager::MouseButtonTappedEvent(const unsigned int& keyCode)
{
	for (auto& object : HMEngine::Core::EventManager::_mouseButtonTappedEventOverriders)
	{
		object->MouseButtonTappedEvent(keyCode);
	}
}

void HMEngine::Core::EventManager::MouseButtonUpEvent(const unsigned int& keyCode)
{
	for (auto& object : HMEngine::Core::EventManager::_mouseButtonUpEventOverriders)
	{
		object->MouseButtonUpEvent(keyCode);
	}
}

void HMEngine::Core::EventManager::RegisterToUpdateEvent(HMEngine::Core::EventObject* object)
{
	HMEngine::Core::EventManager::_updateEventOverriders.insert(object);
}

void HMEngine::Core::EventManager::RegisterToKeyDownEvent(HMEngine::Core::EventObject* object)
{
	HMEngine::Core::EventManager::_keyDownEventOverriders.insert(object);
}

void HMEngine::Core::EventManager::RegisterToKeyTappedEvent(HMEngine::Core::EventObject* object)
{
	HMEngine::Core::EventManager::_keyTappedEventOverriders.insert(object);
}

void HMEngine::Core::EventManager::RegisterToKeyUpEvent(HMEngine::Core::EventObject* object)
{
	HMEngine::Core::EventManager::_keyUpEventOverriders.insert(object);
}

void HMEngine::Core::EventManager::RegisterToMouseButtonDownEvent(HMEngine::Core::EventObject* object)
{
	HMEngine::Core::EventManager::_mouseButtonDownEventOverriders.insert(object);
}

void HMEngine::Core::EventManager::RegisterToMouseButtonTappedEvent(HMEngine::Core::EventObject* object)
{
	HMEngine::Core::EventManager::_mouseButtonTappedEventOverriders.insert(object);
}

void HMEngine::Core::EventManager::RegisterToMouseButtonUpEvent(HMEngine::Core::EventObject* object)
{
	HMEngine::Core::EventManager::_mouseButtonUpEventOverriders.insert(object);
}

void HMEngine::Core::EventManager::RemoveObject(HMEngine::Core::EventObject* object)
{
	HMEngine::Core::EventManager::_updateEventOverriders.erase(object);
	HMEngine::Core::EventManager::_keyDownEventOverriders.erase(object);
	HMEngine::Core::EventManager::_keyTappedEventOverriders.erase(object);
	HMEngine::Core::EventManager::_keyUpEventOverriders.erase(object);
	HMEngine::Core::EventManager::_mouseButtonDownEventOverriders.erase(object);
	HMEngine::Core::EventManager::_mouseButtonTappedEventOverriders.erase(object);
	HMEngine::Core::EventManager::_mouseButtonUpEventOverriders.erase(object);
}