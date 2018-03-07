#include "EventObject.h"

HMEngine::Core::EventObject::EventObject() : _isEnabled(true)
{
}

HMEngine::Core::EventObject::~EventObject()
{
	HMEngine::Core::EventManager::RemoveObject(this);
}

void HMEngine::Core::EventObject::InitializeEventObject()
{
	if (this->_hasUpdateEvent)
		HMEngine::Core::EventManager::RegisterToUpdateEvent(this->_object);
	if (this->_hasKeyDownEvent)
		HMEngine::Core::EventManager::RegisterToKeyDownEvent(this->_object);
	if (this->_hasKeyTappedEvent)
		HMEngine::Core::EventManager::RegisterToKeyTappedEvent(this->_object);
	if (this->_hasKeyUpEvent)
		HMEngine::Core::EventManager::RegisterToKeyUpEvent(this->_object);
	if (this->_hasMouseButtonDownEvent)
		HMEngine::Core::EventManager::RegisterToMouseButtonDownEvent(this->_object);
	if (this->_hasMouseButtonTappedEvent)
		HMEngine::Core::EventManager::RegisterToMouseButtonTappedEvent(this->_object);
	if (this->_hasMouseButtonUpEvent)
		HMEngine::Core::EventManager::RegisterToMouseButtonUpEvent(this->_object);
}