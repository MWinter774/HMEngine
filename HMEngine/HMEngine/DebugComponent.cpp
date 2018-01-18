#include "DebugComponent.h"
#include <iostream>
#include "GameObject.h"
#include "GameEngine.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "GameObject.h"
#include "HardwareInputs.h"
#include "Camera.h"
#include "PointLight.h"
#include "CircleMovement.h"
#include "DirectionalLight.h"

float intesity = 15.0f;
HMEngine::Components::DebugComponent::DebugComponent() : _isAdded(false)
{
	this->_floor = new HMEngine::Core::GameObject("floor");
	this->_floor->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/plane.obj", "./resources/textures/VeryNice.png"));
	this->_floor->AddComponent(HMEngine::Components::DirectionalLight(HMEngine::Components::BaseLight({ 1,1,1 }, 0.07f), { 0,1,1 }));
	this->_floor->GetTransform().SetScale(10, 1, 10);

	this->_fakeCube = new HMEngine::Core::GameObject("fakeCube");
	this->_fakeCube->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/cube.obj", "./resources/textures/bricks.png"));
	HMEngine::Core::Rendering::Camera::GetInstance().SetPosition(0, 0, 5);

	HMEngine::Core::GameObject* crate = nullptr;

	crate = new HMEngine::Core::GameObject("1");
	crate->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/cube.obj", "./resources/textures/bricks.png"));
	crate->GetTransform().SetScale(2, 2, 2);
	crate->GetTransform().SetPosition(10, 2, 10);
	this->_crates.push_back(crate);

	crate = new HMEngine::Core::GameObject("2");
	crate->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/cube.obj", "./resources/textures/bricks.png"));
	crate->GetTransform().SetScale(2, 2, 2);
	crate->GetTransform().SetPosition(10, 2, -10);
	this->_crates.push_back(crate);

	crate = new HMEngine::Core::GameObject("3");
	crate->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/cube.obj", "./resources/textures/bricks.png"));
	crate->GetTransform().SetScale(2, 2, 2);
	crate->GetTransform().SetPosition(-10, 2, -10);
	this->_crates.push_back(crate);

	crate = new HMEngine::Core::GameObject("4");
	crate->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/cube.obj", "./resources/textures/bricks.png"));
	crate->GetTransform().SetScale(2, 2, 2);
	crate->GetTransform().SetPosition(-10, 2, 10);
	this->_crates.push_back(crate);

	HMEngine::Core::GameObject* pointLight = nullptr;

	pointLight = new HMEngine::Core::GameObject("p1");
	pointLight->AddComponent(HMEngine::Components::PointLight(HMEngine::Components::BaseLight({ 1,0,0 }, intesity), { 0,0,1 }, 50.0f));
	pointLight->GetTransform().SetScale(2, 2, 2);
	pointLight->GetTransform().SetPosition(-10, 3, 10);
	this->_pointLights.push_back(pointLight);

	pointLight = new HMEngine::Core::GameObject("p2");
	pointLight->AddComponent(HMEngine::Components::PointLight(HMEngine::Components::BaseLight({ 0,1,0 }, intesity), { 0,0,1 }, 50.0f));
	pointLight->GetTransform().SetScale(2, 2, 2);
	pointLight->GetTransform().SetPosition(-10, 3, -10);
	this->_pointLights.push_back(pointLight);

	pointLight = new HMEngine::Core::GameObject("p3");
	pointLight->AddComponent(HMEngine::Components::PointLight(HMEngine::Components::BaseLight({ 0,1,1 }, intesity), { 0,0,1 }, 50.0f));
	pointLight->GetTransform().SetScale(2, 2, 2);
	pointLight->GetTransform().SetPosition(10, 3, 10);
	this->_pointLights.push_back(pointLight);

	pointLight = new HMEngine::Core::GameObject("p4");
	pointLight->AddComponent(HMEngine::Components::PointLight(HMEngine::Components::BaseLight({ 0,0,1 }, intesity), { 0,0,1 }, 50.0f));
	pointLight->GetTransform().SetScale(2, 2, 2);
	pointLight->GetTransform().SetPosition(10, 3, -10);
	this->_pointLights.push_back(pointLight);

	pointLight = new HMEngine::Core::GameObject("pCenter");
	pointLight->AddComponent(HMEngine::Components::PointLight(HMEngine::Components::BaseLight({ 1,1,1 }, 20.0f), { 0,0,1 }, 50.0f));
	pointLight->GetTransform().SetScale(2, 2, 2);
	pointLight->GetTransform().SetPosition(0, 3, 0);
	this->_pointLights.push_back(pointLight);

	HMEngine::Core::GameObject* monkey = nullptr;

	monkey = new HMEngine::Core::GameObject("m1");
	monkey->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/monkey.obj", "./resources/textures/bricks.png"));
	monkey->GetTransform().SetScale(8, 8, 8);
	monkey->GetTransform().SetPosition(55, 8, 55);
	this->_monkies.push_back(monkey);

	monkey = new HMEngine::Core::GameObject("m2");
	monkey->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/monkey.obj", "./resources/textures/bricks.png"));
	monkey->GetTransform().SetScale(8, 8, 8);
	monkey->GetTransform().SetPosition(-55, 8, 55);
	this->_monkies.push_back(monkey);

	monkey = new HMEngine::Core::GameObject("m3");
	monkey->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/monkey.obj", "./resources/textures/bricks.png"));
	monkey->GetTransform().SetScale(8, 8, 8);
	monkey->GetTransform().SetPosition(55, 8, -55);
	this->_monkies.push_back(monkey);

	monkey = new HMEngine::Core::GameObject("m4");
	monkey->AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/monkey.obj", "./resources/textures/bricks.png"));
	monkey->GetTransform().SetScale(8, 8, 8);
	monkey->GetTransform().SetPosition(-55, 8, -55);
	this->_monkies.push_back(monkey);

	HMEngine::Core::GameObject* pointLightMonkey = nullptr;

	pointLightMonkey = new HMEngine::Core::GameObject("pm1");
	pointLightMonkey->AddComponent(HMEngine::Components::PointLight(HMEngine::Components::BaseLight({ 1,1,0 }, intesity), { 0,0,1 }, 50.0f));
	pointLightMonkey->AddComponent(HMEngine::Components::CircleMovement(55, 55, 18));
	pointLightMonkey->GetTransform().SetScale(2, 2, 2);
	this->_pointLightMonkies.push_back(pointLightMonkey);

	pointLightMonkey = new HMEngine::Core::GameObject("pm2");
	pointLightMonkey->AddComponent(HMEngine::Components::PointLight(HMEngine::Components::BaseLight({ 0.5,0.2,0.4 }, intesity), { 0,0,1 }, 50.0f));
	pointLightMonkey->AddComponent(HMEngine::Components::CircleMovement(-55, 55, 18));
	pointLightMonkey->GetTransform().SetScale(2, 2, 2);
	this->_pointLightMonkies.push_back(pointLightMonkey);

	pointLightMonkey = new HMEngine::Core::GameObject("pm3");
	pointLightMonkey->AddComponent(HMEngine::Components::PointLight(HMEngine::Components::BaseLight({ 0.1,0.9,0 }, intesity), { 0,0,1 }, 50.0f));
	pointLightMonkey->AddComponent(HMEngine::Components::CircleMovement(55, -55, 18));
	pointLightMonkey->GetTransform().SetScale(2, 2, 2);
	this->_pointLightMonkies.push_back(pointLightMonkey);

	pointLightMonkey = new HMEngine::Core::GameObject("pm4");
	pointLightMonkey->AddComponent(HMEngine::Components::PointLight(HMEngine::Components::BaseLight({ 0,0.4,0.6 }, intesity), { 0,0,1 }, 50.0f));
	pointLightMonkey->AddComponent(HMEngine::Components::CircleMovement(-55, -55, 18));
	pointLightMonkey->GetTransform().SetScale(2, 2, 2);
	this->_pointLightMonkies.push_back(pointLightMonkey);
}

HMEngine::Components::DebugComponent::~DebugComponent()
{
	delete this->_floor;
	delete this->_fakeCube;
	for (auto& crate : this->_crates)
	{
		delete crate;
	}
	for (auto& pointLight : this->_pointLights)
	{
		delete pointLight;
	}
	for (auto& monkey : this->_monkies)
	{
		delete monkey;
	}
	for (auto& pointLightMonkey : this->_pointLightMonkies)
	{
		delete pointLightMonkey;
	}
}

HMEngine::Components::DebugComponent::DebugComponent(const HMEngine::Components::DebugComponent& other)
{
	this->_floor = new HMEngine::Core::GameObject(*other._floor);
	this->_fakeCube = new HMEngine::Core::GameObject(*other._fakeCube);
	this->_isAdded = other._isAdded;
	for (auto& crate : other._crates)
	{
		this->_crates.push_back(new HMEngine::Core::GameObject(*crate));
	}
	for (auto& pointLight : other._pointLights)
	{
		this->_pointLights.push_back(new HMEngine::Core::GameObject(*pointLight));
	}
	for (auto& monkey : other._monkies)
	{
		this->_monkies.push_back(new HMEngine::Core::GameObject(*monkey));
	}
	for (auto& pointLightMonkey : other._pointLightMonkies)
	{
		this->_pointLightMonkies.push_back(new HMEngine::Core::GameObject(*pointLightMonkey));
	}
}

HMEngine::Components::Component* HMEngine::Components::DebugComponent::Clone()
{
	return new HMEngine::Components::DebugComponent(*this);
}

void HMEngine::Components::DebugComponent::AttachToGameObjectEvent()
{
	this->AddGameObject(*this->_fakeCube);
}

void HMEngine::Components::DebugComponent::UpdateEvent()
{
	if (!this->_isAdded && HMEngine::Core::Hardware::HardwareInputs::IsKeyTapped(SDL_SCANCODE_F))
	{
		this->_isAdded = true;
		this->AddGameObject(*this->_floor);
		this->RemoveGameObject("fakeCube_Copy_Copy");
		HMEngine::Core::Rendering::Camera::GetInstance().SetPosition(0, 2, 10);
		for (auto& crate : this->_crates)
		{
			this->AddGameObject(*crate);
		}
		for (auto& pointLight : this->_pointLights)
		{
			this->AddGameObject(*pointLight);
		}
		for (auto& monkey : this->_monkies)
		{
			this->AddGameObject(*monkey);
		}
		for (auto& pointLightMonkey : this->_pointLightMonkies)
		{
			this->AddGameObject(*pointLightMonkey);
		}
	}
}