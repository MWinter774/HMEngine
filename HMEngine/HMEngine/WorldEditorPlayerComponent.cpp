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

void OnGameObjectCategoryButtonClick(HMEngine::UI::Button* gameObjectCategoryButton)
{
	std::cout << gameObjectCategoryButton->GetName() << std::endl;
}

HMEngine::Core::WorldEditor::WorldEditorPlayerComponent::WorldEditorPlayerComponent(HMEngine::Components::CameraController& cameraController) :
	_menu(new HMEngine::UI::ContextMenu("cntxtmnuWorldEditor", HMEngine::GameSettings::GetScreenCenter())), _cameraController(&cameraController),
	_addGameObjectMenu(new HMEngine::UI::Menu("mnuAddGameObject", HMEngine::GameSettings::GetScreenCenter(), glm::vec2(400, 650),
		"./resources/UITextures/AddGameObjectMenu.png")), 
	_normalGameObjectScreen(new HMEngine::UI::QuadCollection("scrnNormalGameObject", HMEngine::GameSettings::GetScreenCenter(), glm::vec2()))
{
	this->InitializeEvents<WorldEditorPlayerComponent>(this);
	this->_menu->SetCenter(glm::vec2(600, 360));
	this->_menu->AddButton("AddGameObjectButton", "Add Game Object", [this](HMEngine::UI::Button* btn) { this->_addGameObjectMenu->Show(); this->_menu->Hide(); });
	this->_menu->Hide();


	this->_addGameObjectMenu->AddButton("gameObjectCategory", "./resources/UITextures/AddGameObjectReleased.png",
		"./resources/UITextures/AddGameObjectHovered.png", "./resources/UITextures/AddGameObjectPressed.png", glm::vec2(31, 31), glm::vec2(50, 50), "",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.5f, [this](HMEngine::UI::Button* btn)
	{
		this->_normalGameObjectScreen->Show();
	});
	this->_addGameObjectMenu->Hide();

	this->_normalGameObjectScreen->AddQuad(new HMEngine::UI::Label("lblGameObjectName", glm::vec2(500, 200), "Game Object Name:", HMEngine::Fonts::ARIAL,
		glm::vec3(), 0.8f));
	this->_normalGameObjectScreen->AddQuad(new HMEngine::UI::TextBox("txtboxGameObjectName", glm::vec2(650, 200), glm::vec2(120, 25), HMEngine::Fonts::ARIAL));
	this->_normalGameObjectScreen->Hide();
}

HMEngine::Core::WorldEditor::WorldEditorPlayerComponent::~WorldEditorPlayerComponent()
{
}

HMEngine::Core::WorldEditor::WorldEditorPlayerComponent::WorldEditorPlayerComponent(const HMEngine::Core::WorldEditor::WorldEditorPlayerComponent& other) :
	HMEngine::Components::Component(other), _menu(new HMEngine::UI::ContextMenu(*other._menu)), _cameraController(other._cameraController),
	_addGameObjectMenu(new HMEngine::UI::Menu(*other._addGameObjectMenu))
{
	this->InitializeEvents<WorldEditorPlayerComponent>(this);
}

HMEngine::Core::WorldEditor::WorldEditorPlayerComponent& HMEngine::Core::WorldEditor::WorldEditorPlayerComponent::operator=
(const HMEngine::Core::WorldEditor::WorldEditorPlayerComponent& other)
{
	if (this != &other)
	{
		this->InitializeEvents<WorldEditorPlayerComponent>(this);
		delete this->_menu;
		delete this->_addGameObjectMenu;

		this->_menu = new HMEngine::UI::ContextMenu(*other._menu);
		this->_addGameObjectMenu = new HMEngine::UI::Menu(*other._addGameObjectMenu);
		this->_cameraController = other._cameraController;
	}

	return *this;
}

void HMEngine::Core::WorldEditor::WorldEditorPlayerComponent::MouseButtonDownEvent(const unsigned int& mouseButton)
{
	bool cursorOnAddGameObjectMenu = HMEngine::Core::Hardware::HardwareInputs::IsCursorWithinBoundaries(this->_addGameObjectMenu->GetTopLeft(), this->_addGameObjectMenu->GetBottomRight());
	bool cursorOnMenu = HMEngine::Core::Hardware::HardwareInputs::IsCursorWithinBoundaries(this->_menu->GetTopLeft(), this->_menu->GetBottomRight());

	if (cursorOnMenu && !this->_addGameObjectMenu->IsVisible()) //if the context menu is on focus
	{
		if (mouseButton == 3) //right click
		{
			this->_parentObject->GetGameEngine().UnlockCursor();
			this->_parentObject->GetGameEngine().SetMouseVisible(true);
			this->_cameraController->Deactivate();
			this->_menu->Show();
		}
	}
	else if (!cursorOnAddGameObjectMenu || !this->_addGameObjectMenu->IsVisible())
	{
		this->_parentObject->GetGameEngine().LockCursor();
		this->_parentObject->GetGameEngine().SetMouseVisible(false);
		this->_cameraController->Activate();
		this->_menu->Hide();
		this->_addGameObjectMenu->Hide();
		this->_normalGameObjectScreen->Hide();
	}
}

void HMEngine::Core::WorldEditor::WorldEditorPlayerComponent::AttachToGameObjectEvent()
{
	this->AddUI(this->_menu);
	this->AddUI(this->_addGameObjectMenu);
	this->AddUI(this->_normalGameObjectScreen);
}