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

float n1 = 6.0f;
float n2 = 10;

void HMEngine::Components::DebugComponent::UpdateEvent()
{
	this->_count++;
	if (this->_count % 60 == 0)
	{
		//auto a = HMEngine::Core::GameObject(std::to_string(this->_count));
		//a.AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/cube.obj", "./resources/textures/VeryNice.png"));
		//a.GetTransform().SetPosition(float(std::rand() % 10 + 1), float(std::rand() % 10 + 1), 0);
		//this->AddGameObject(a);
	}
	if (this->_parentObject->GetName() == "d")
	{
		this->_parentObject->GetTransform().SetPositionX(float(sin(this->_count / n2) * n1));
	}
	else if (this->_parentObject->GetName() == "d1")
	{
		this->_parentObject->GetTransform().SetPositionZ(float(sin(this->_count / n2) * n1));
	}
	else if (this->_parentObject->GetName() == "d2")
	{
		this->_parentObject->GetTransform().SetPositionX(float(sin(this->_count / n2) * n1));
		this->_parentObject->GetTransform().SetPositionZ(float(sin(this->_count / n2) * n1));
	}
}