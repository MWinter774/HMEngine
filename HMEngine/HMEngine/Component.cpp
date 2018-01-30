#include "Component.h"
#include "GameObject.h"
#include "GameEngine.h"

HMEngine::Components::Component::Component() : _parentObject(nullptr), _isAttachedToGameObject(false)
{
}

HMEngine::Components::Component::~Component()
{
}

std::vector<HMEngine::Core::GameObject*> HMEngine::Components::Component::GetGameObjects() const
{
	return this->_parentObject->GetGameEngine().GetGameObjects();
}

HMEngine::Core::GameObject* HMEngine::Components::Component::GetGameObject(const std::string& name) const
{
	return this->_parentObject->GetGameEngine().GetGameObject(name);
}

void HMEngine::Components::Component::AddGameObject(const HMEngine::Core::GameObject& go) const
{
	this->_parentObject->GetGameEngine().AddGameObject(go);
}

void HMEngine::Components::Component::AddGameObject(HMEngine::Core::GameObject* go) const
{
	this->_parentObject->GetGameEngine().AddGameObject(go);
}

void HMEngine::Components::Component::RemoveGameObject(const std::string& name) const
{
	this->_parentObject->GetGameEngine().RemoveGameObject(name);
}

void HMEngine::Components::Component::AttachToGameObject()
{
	this->_isAttachedToGameObject = true;
	this->AttachToGameObjectEvent();
}
