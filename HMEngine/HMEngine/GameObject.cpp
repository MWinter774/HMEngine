#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "Utilities.h"
#include <iostream>
#include <memory>
#include "MeshRenderer.h"
#include "Collider.h"

HMEngine::Core::GameObject::GameObject(const std::string& name) : _transform(new HMEngine::Core::Transform()), _components(), _gameEngine(nullptr), _name(name),
_meshRenderer(nullptr), _color(1, 1, 1)
{
}

HMEngine::Core::GameObject::~GameObject()
{
	delete this->_transform;
	for (auto& component : this->_components)
	{
		delete component;
	}
}

HMEngine::Core::GameObject::GameObject(const HMEngine::Core::GameObject& other) : _transform(new HMEngine::Core::Transform(*other._transform)), _name(other._name), _gameEngine(other._gameEngine)
{
	HMEngine::Components::Component* newComponent = nullptr;
	for (auto& component : other._components)
	{
		newComponent = component->Clone();
		if (auto meshRenderer = dynamic_cast<HMEngine::Components::MeshRenderer*>(newComponent))
			this->_meshRenderer = meshRenderer;
		if (auto collider = dynamic_cast<HMEngine::Core::Physics::Colliders::Collider*>(newComponent))
			this->_collider = collider;
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
			if (auto meshRenderer = dynamic_cast<HMEngine::Components::MeshRenderer*>(newComponent))
				this->_meshRenderer = meshRenderer;
			if (auto collider = dynamic_cast<HMEngine::Core::Physics::Colliders::Collider*>(newComponent))
				this->_collider = collider;
			newComponent->_parentObject = this;
			this->_components.push_back(newComponent);
		}
		this->_name = other._name + "_Copy";
		this->_gameEngine = other._gameEngine;
	}

	return *this;
}

void HMEngine::Core::GameObject::SetTransform(const HMEngine::Core::Transform& transform)
{
	*this->_transform = transform;
}

void HMEngine::Core::GameObject::AddComponent(HMEngine::Components::Component& component)
{
	HMEngine::Components::Component* newComponent = component.Clone();
	if (auto meshRenderer = dynamic_cast<HMEngine::Components::MeshRenderer*>(newComponent))
		this->_meshRenderer = meshRenderer;
	if (auto collider = dynamic_cast<HMEngine::Core::Physics::Colliders::Collider*>(newComponent))
		this->_collider = collider;
	newComponent->_parentObject = this;
	this->_components.push_back(newComponent);
}

void HMEngine::Core::GameObject::AddComponent(HMEngine::Components::Component* component)
{
	if (auto meshRenderer = dynamic_cast<HMEngine::Components::MeshRenderer*>(component))
		this->_meshRenderer = meshRenderer;
	if (auto collider = dynamic_cast<HMEngine::Core::Physics::Colliders::Collider*>(component))
		this->_collider = collider;
	component->_parentObject = this;
	this->_components.push_back(component);
}

void HMEngine::Core::GameObject::Move(const glm::vec3& direction, float amount)
{
	if (this->_collider != nullptr)
	{
		this->_collider->AddPosition(direction * amount);
	}
	else
	{
		this->_transform->AddPosition(direction * amount);
	}
}

/*
Special constructor that keeps the name of the original game object.
*/
HMEngine::Core::GameObject::GameObject(const HMEngine::Core::GameObject& other, bool _1) : _transform(new HMEngine::Core::Transform(*other._transform)), _name(other._name), _gameEngine(other._gameEngine)
{
	HMEngine::Components::Component* newComponent = nullptr;
	for (auto& component : other._components)
	{
		newComponent = component->Clone();
		if (auto meshRenderer = dynamic_cast<HMEngine::Components::MeshRenderer*>(newComponent))
			this->_meshRenderer = meshRenderer;
		newComponent->_parentObject = this;
		this->_components.push_back(newComponent);
	}
}

void HMEngine::Core::GameObject::AttachToGameEngine()
{
	this->AttachToGameEngineEvent();
	for (auto& attachToGameEngineEvent : this->_attachToGameEngineEvents)
		attachToGameEngineEvent();
	for (auto& component : this->_components)
	{
		component->InitializeEventObject();
		component->AttachToGameObject();
	}
}