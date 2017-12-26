#include "Component.h"
#include "GameObject.h"

void HMEngine::Components::Draw::Render()
{
	if (this->_parentObject != nullptr)
		this->_parentObject->Draw();
}

HMEngine::Components::Component::Component() : _parentObject(nullptr)
{
}

HMEngine::Components::Component::~Component()
{
}
