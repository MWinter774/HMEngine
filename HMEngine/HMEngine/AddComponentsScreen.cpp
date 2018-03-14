#include "AddComponentsScreen.h"
#include "GameEngine.h"
#include "Label.h"
#include "Fonts.h"
#include "TextBox.h"
#include "List.h"
#include "Button.h"
#include "MeshRendererComponentScreen.h"
#include "CircleMovementComponentScreen.h"
#include "DirectionalLightComponentScreen.h"
#include "PointLightComponentScreen.h"
#include <iostream>

HMEngine::Core::WorldEditor::AddComponentsScreen::AddComponentsScreen(const glm::vec2& centerPos,
	const std::function<void(HMEngine::Components::Component*)>& addComponentEvent) :
	HMEngine::UI::Screen("scrnAddComponents", centerPos, glm::vec2(500, 300)),
	_lblAddComponentsTitle(new HMEngine::UI::Label("lblAddComponentsTitle", glm::vec2(centerPos.x, centerPos.y - 130), "Add Components", HMEngine::Fonts::ARIAL,
		glm::vec3(), 1.0f)),
	_scrnMeshRenderer(new HMEngine::Core::WorldEditor::ComponentScreens::MeshRendererComponentScreen(centerPos)),
	_scrnCircleMovement(new HMEngine::Core::WorldEditor::ComponentScreens::CircleMovementComponentScreen(centerPos)),
	_scrnDirectionalLight(new HMEngine::Core::WorldEditor::ComponentScreens::DirectionalLightComponentScreen(centerPos)),
	_scrnPointLight(new HMEngine::Core::WorldEditor::ComponentScreens::PointLightComponentScreen(centerPos)),
	_txtComponentSearch(new HMEngine::UI::TextBox("txtComponentSerach", glm::vec2(centerPos.x, centerPos.y - 90), glm::vec2(400, 25), HMEngine::Fonts::ARIAL)),
	_lstComponentsList(new HMEngine::UI::List("lstComponentsList", glm::vec2(centerPos.x, centerPos.y + 30), glm::vec2(400, 200),
		"./resources/UITextures/listBackground.png")),
	_addComponentEvent(addComponentEvent)
{
	this->_scrnMeshRenderer->_addComponentEvent = std::bind(&HMEngine::Core::WorldEditor::AddComponentsScreen::ComponentAddedEvent, this, std::placeholders::_1);
	this->_scrnMeshRenderer->_hideEvent = std::bind(&HMEngine::Core::WorldEditor::AddComponentsScreen::EnableScreens, this);
	this->_scrnCircleMovement->_addComponentEvent = std::bind(&HMEngine::Core::WorldEditor::AddComponentsScreen::ComponentAddedEvent, this, std::placeholders::_1);
	this->_scrnCircleMovement->_hideEvent = std::bind(&HMEngine::Core::WorldEditor::AddComponentsScreen::EnableScreens, this);
	this->_scrnDirectionalLight->_addComponentEvent = std::bind(&HMEngine::Core::WorldEditor::AddComponentsScreen::ComponentAddedEvent, this, std::placeholders::_1);
	this->_scrnDirectionalLight->_hideEvent = std::bind(&HMEngine::Core::WorldEditor::AddComponentsScreen::EnableScreens, this);
	this->_scrnPointLight->_addComponentEvent = std::bind(&HMEngine::Core::WorldEditor::AddComponentsScreen::ComponentAddedEvent, this, std::placeholders::_1);
	this->_scrnPointLight->_hideEvent = std::bind(&HMEngine::Core::WorldEditor::AddComponentsScreen::EnableScreens, this);

	this->_btnMeshRenderer = this->_lstComponentsList->AddButton("MeshRenderer", [this](HMEngine::UI::Button* btn) { this->_scrnMeshRenderer->Show(); this->DisableScreens(this->_scrnMeshRenderer); });
	this->_btnCircleMovement = this->_lstComponentsList->AddButton("CircleMovement", [this](HMEngine::UI::Button* btn) { this->_scrnCircleMovement->Show(); this->DisableScreens(this->_scrnCircleMovement); });
	this->_btnDirectionalLight = this->_lstComponentsList->AddButton("DirectionalLight", [this](HMEngine::UI::Button* btn) { this->_scrnDirectionalLight->Show(); this->DisableScreens(this->_scrnDirectionalLight); });
	this->_btnPointLight = this->_lstComponentsList->AddButton("PointLight", [this](HMEngine::UI::Button* btn) { this->_scrnPointLight->Show(); this->DisableScreens(this->_scrnPointLight); });

	this->SetBackground("./resources/UITextures/AddGameObjectMenu.png");
	this->AddQuad(this->_lblAddComponentsTitle);
	this->AddQuad(this->_txtComponentSearch);
	this->AddQuad(this->_lstComponentsList);
	this->AddQuad(this->_scrnMeshRenderer);
	this->AddQuad(this->_scrnCircleMovement);
	this->AddQuad(this->_scrnPointLight);
	this->AddQuad(this->_scrnDirectionalLight);
	this->Hide();
}

HMEngine::Core::WorldEditor::AddComponentsScreen::~AddComponentsScreen()
{
}

void HMEngine::Core::WorldEditor::AddComponentsScreen::ShowEvent()
{
	this->_scrnMeshRenderer->Hide();
	this->_scrnCircleMovement->Hide();
	this->_scrnPointLight->Hide();
	this->_scrnDirectionalLight->Hide();

	this->_btnCircleMovement->_isEnabled = true;
	this->_btnDirectionalLight->_isEnabled = true;
	this->_btnMeshRenderer->_isEnabled = true;
	this->_btnPointLight->_isEnabled = true;
}

void HMEngine::Core::WorldEditor::AddComponentsScreen::ComponentAddedEvent(HMEngine::Components::Component* component)
{
	this->_scrnMeshRenderer->Hide();
	this->_scrnCircleMovement->Hide();
	this->_scrnPointLight->Hide();
	this->_scrnDirectionalLight->Hide();
	this->_addComponentEvent(component);
}

void HMEngine::Core::WorldEditor::AddComponentsScreen::DisableScreens(HMEngine::UI::Screen* except)
{
	if (except != this->_scrnCircleMovement)
	{
		this->_scrnCircleMovement->DisableEvents();
		this->_btnCircleMovement->_isEnabled = false;
	}
	if (except != this->_scrnDirectionalLight)
	{
		this->_scrnDirectionalLight->DisableEvents();
		this->_btnDirectionalLight->_isEnabled = false;
	}
	if (except != this->_scrnMeshRenderer)
	{
		this->_scrnMeshRenderer->DisableEvents();
		this->_btnMeshRenderer->_isEnabled = false;
	}
	if (except != this->_scrnPointLight)
	{
		this->_scrnPointLight->DisableEvents();
		this->_btnPointLight->_isEnabled = false;
	}
}

void HMEngine::Core::WorldEditor::AddComponentsScreen::EnableScreens()
{
	/*this->_scrnCircleMovement->EnableEvents();
	this->_btnCircleMovement->_isEnabled = true;
	this->_scrnDirectionalLight->EnableEvents();
	this->_btnDirectionalLight->_isEnabled = true;
	this->_scrnMeshRenderer->EnableEvents();
	this->_btnMeshRenderer->_isEnabled = true;
	this->_scrnPointLight->EnableEvents();
	this->_btnPointLight->_isEnabled = true;*/

	this->_btnCircleMovement->_isEnabled = true;
	this->_btnDirectionalLight->_isEnabled = true;
	this->_btnMeshRenderer->_isEnabled = true;
	this->_btnPointLight->_isEnabled = true;
}