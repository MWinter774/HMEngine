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
	if (this->_count % 60 == 0)
	{
		auto a = HMEngine::Core::GameObject(std::to_string(this->_count));
		a.AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/cube.obj", "./resources/textures/VeryNice.png"));
		a.GetTransform().SetPosition(float(std::rand() % 10 + 1), float(std::rand() % 10 + 1), 0);
		this->AddGameObject(a);
	}
}