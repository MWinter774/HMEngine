#include "GameObject.h"
#include "Transform.h"

HMEngine::Core::GameObject::GameObject() : _transform(new HMEngine::Core::Transform()), _components()
{
}

HMEngine::Core::GameObject::~GameObject()
{
	delete this->_transform;
}

HMEngine::Core::GameObject::GameObject(const HMEngine::Core::GameObject& other) : _transform(new HMEngine::Core::Transform(*other._transform))
{
	for (auto& component : other._components)
	{
		auto newComponent = component;
		newComponent.get()._parentObject = this;
		this->_components.push_back(newComponent);
	}
}

HMEngine::Core::GameObject& HMEngine::Core::GameObject::operator=(const HMEngine::Core::GameObject& other)
{
	if (this != &other)
	{
		*this->_transform = *other._transform;
		this->_components = other._components;
	}

	return *this;
}

void HMEngine::Core::GameObject::RotateY(float speed)
{
	this->_transform->AddRotationY(speed);
}

void HMEngine::Core::GameObject::SetTransform(const HMEngine::Core::Transform& transform)
{
	*this->_transform = transform;
}

void HMEngine::Core::GameObject::Draw() const
{
	for (auto& component : this->_components)
	{
		component.get().RenderEvent(); //invoke the rendering event
	}
}

void HMEngine::Core::GameObject::AddComponent(HMEngine::Components::Component& component)
{
	component._parentObject = this;
	this->_components.push_back(component);
}