#include "WorldEditorPlayerComponent.h"
#include "ContextMenu.h"
#include "GameObject.h"
#include "GameEngine.h"
#include "CameraController.h"
#include "HardwareInputs.h"
#include "Menu.h"
#include "Fonts.h"
#include "Button.h"
#include "QuadCollection.h"
#include "Label.h"
#include "TextBox.h"
#include "AddNormalGameObjectScreen.h"

HMEngine::Core::WorldEditor::WorldEditorPlayerComponent::WorldEditorPlayerComponent(HMEngine::Components::CameraController& cameraController) :
	_contextMenu(new HMEngine::UI::ContextMenu("cntxtmnuWorldEditor", HMEngine::GameSettings::GetScreenCenter())), _cameraController(&cameraController),
	_addGameObjectScreen(new HMEngine::Core::WorldEditor::AddNormalGameObjectScreen(HMEngine::GameSettings::GetScreenCenter()))
{
	this->InitializeEvents<WorldEditorPlayerComponent>(this);
	this->_contextMenu->SetCenter(HMEngine::GameSettings::GetScreenCenter());
	this->_contextMenu->AddButton("AddGameObjectButton", "Add Game Object", [this](HMEngine::UI::Button* btn) { this->_addGameObjectScreen->Show(); this->_contextMenu->Hide(); });
	this->_contextMenu->Hide();

	this->_addGameObjectScreen->SetBackground("./resources/UITextures/AddGameObjectMenu.png");
	this->_addGameObjectScreen->Hide();
}

HMEngine::Core::WorldEditor::WorldEditorPlayerComponent::~WorldEditorPlayerComponent()
{
}

HMEngine::Core::WorldEditor::WorldEditorPlayerComponent::WorldEditorPlayerComponent(const HMEngine::Core::WorldEditor::WorldEditorPlayerComponent& other) :
	HMEngine::Components::Component(other), _contextMenu(new HMEngine::UI::ContextMenu(*other._contextMenu)), _cameraController(other._cameraController)
{
	this->InitializeEvents<WorldEditorPlayerComponent>(this);
}

HMEngine::Core::WorldEditor::WorldEditorPlayerComponent& HMEngine::Core::WorldEditor::WorldEditorPlayerComponent::operator=
(const HMEngine::Core::WorldEditor::WorldEditorPlayerComponent& other)
{
	if (this != &other)
	{
		this->InitializeEvents<WorldEditorPlayerComponent>(this);
		delete this->_contextMenu;

		this->_contextMenu = new HMEngine::UI::ContextMenu(*other._contextMenu);
		this->_cameraController = other._cameraController;
	}

	return *this;
}

void HMEngine::Core::WorldEditor::WorldEditorPlayerComponent::MouseButtonDownEvent(const unsigned int& mouseButton)
{
	bool cursorOnMenu = HMEngine::Core::Hardware::HardwareInputs::IsCursorWithinBoundaries(this->_contextMenu->GetTopLeft(), this->_contextMenu->GetBottomRight());
	bool cursorOnAddGameObjectMenu = HMEngine::Core::Hardware::HardwareInputs::IsCursorWithinBoundaries(this->_addGameObjectScreen->GetTopLeft(), 
		this->_addGameObjectScreen->GetBottomRight());

	if (cursorOnMenu) //if the context menu is on focus
	{
		if (mouseButton == 3) //right click
		{
			this->_parentObject->GetGameEngine().UnlockCursor();
			this->_parentObject->GetGameEngine().SetMouseVisible(true);
			this->_cameraController->Deactivate();
			this->_contextMenu->Show();
		}
	}
	else if(!this->_addGameObjectScreen->IsChildFocus())
	{
		this->_parentObject->GetGameEngine().LockCursor();
		this->_parentObject->GetGameEngine().SetMouseVisible(false);
		this->_cameraController->Activate();
		this->_contextMenu->Hide();
	}
}

void HMEngine::Core::WorldEditor::WorldEditorPlayerComponent::AttachToGameObjectEvent()
{
	this->AddUI(this->_contextMenu);
	this->AddUI(this->_addGameObjectScreen);
}