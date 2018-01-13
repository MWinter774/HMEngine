#include "DebugComponent.h"
#include <iostream>
#include "GameObject.h"
#include "GameEngine.h"

HMEngine::Components::DebugComponent::DebugComponent()
{
}

HMEngine::Components::DebugComponent::~DebugComponent()
{
}

HMEngine::Components::Component* HMEngine::Components::DebugComponent::Clone()
{
	return new HMEngine::Components::DebugComponent();
}

void HMEngine::Components::DebugComponent::UpdateEvent()
{
	this->_count++;
	if (this->_count % 60 == 0)
	{
		std::cout << "1 Second passed..." << std::endl;
		this->_parentObject->GetGameEngine().AddGameObject(HMEngine::Core::GameObject(std::to_string(this->_count)));
	}
}