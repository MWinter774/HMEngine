#include "GameObject.h"

HMEngine::Core::GameObject::GameObject() : _transform(new HMEngine::Core::Transform())
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

HMEngine::Core::GameObject::GameObject(const HMEngine::Core::GameObject& other)
{
	this->_transform = new HMEngine::Core::Transform(*other._transform);
	this->_components = other._components;
}

HMEngine::Core::GameObject& HMEngine::Core::GameObject::operator=(const HMEngine::Core::GameObject& other)
{
	if (this != &other)
	{
		*this = HMEngine::Core::GameObject();
		this->SetTransform(other.GetTransform());
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
		component->RenderEvent();
	}
}

void HMEngine::Core::GameObject::AddComponent(HMEngine::Components::Component* component)
{
	component->_parentObject = this;
	this->_components.push_back(component);
}