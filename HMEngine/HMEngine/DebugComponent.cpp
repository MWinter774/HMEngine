#include "DebugComponent.h"
#include <iostream>
#include "GameObject.h"
#include "GameEngine.h"
#include "Transform.h"
#include "MeshRenderer.h"

HMEngine::Components::DebugComponent::DebugComponent()
{
}

HMEngine::Components::DebugComponent::~DebugComponent()
{
}

HMEngine::Components::Component* HMEngine::Components::DebugComponent::Clone()
{
	return new HMEngine::Components::DebugComponent(*this);
}

void HMEngine::Components::DebugComponent::UpdateEvent()
{
	this->_count++;
	if (this->_count % 10 == 0)
	{
	}
}