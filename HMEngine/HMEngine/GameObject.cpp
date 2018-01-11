#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include <iostream>
#include <memory>

HMEngine::Core::GameObject::GameObject() : _transform(new HMEngine::Core::Transform()), _components()
{
}

HMEngine::Core::GameObject::~GameObject()
{
	delete this->_transform;
	for(auto& component : this->_components)
	{
		delete component;
	}
}

HMEngine::Core::GameObject::GameObject(const HMEngine::Core::GameObject& other) : _transform(new HMEngine::Core::Transform(*other._transform))
{
	HMEngine::Components::Component* newComponent = nullptr;
	for (auto& component : other._components)
	{
		newComponent = component->Clone();
		newComponent->_parentObject = this;
		this->_components.push_back(newComponent);
	}
}

HMEngine::Core::GameObject& HMEngine::Core::GameObject::operator=(const HMEngine::Core::GameObject& other)
{
	if (this != &other)
	{
		*this->_transform = *other._transform;

		HMEngine::Components::Component* newComponent = nullptr;
		for (auto& component : this->_components)
		{
			delete component;
		}
		this->_components.clear();

		for (auto& component : other._components)
		{
			newComponent = component->Clone();
			newComponent->_parentObject = this;
			this->_components.push_back(newComponent);
		}
	}

	return *this;
}

void HMEngine::Core::GameObject::SetTransform(const HMEngine::Core::Transform& transform)
{
	*this->_transform = transform;
}

void HMEngine::Core::GameObject::Draw() const
{
	for (auto& component : this->_components)
	{
		component->RenderEvent(); //invoke the rendering event
	}
}

void HMEngine::Core::GameObject::Update() const
{
	for (auto& component : this->_components)
	{
		component->UpdateEvent(); //invoke the rendering event
	}
}

void HMEngine::Core::GameObject::AddComponent(HMEngine::Components::Component& component)
{
	HMEngine::Components::Component* newComponent = component.Clone();
	newComponent->_parentObject = this;
	this->_components.push_back(newComponent);
}

void HMEngine::Core::GameObject::AttachToGameEngine()
{
	for (auto& component : this->_components)
	{
		component->AttachToGameObjectEvent();
	}
}
