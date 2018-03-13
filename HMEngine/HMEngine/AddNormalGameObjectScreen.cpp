#include "AddNormalGameObjectScreen.h"
#include "QuadCollection.h"
#include "TextBox.h"
#include "Button.h"
#include "Label.h"
#include "Fonts.h"
#include "GameEngine.h"
#include "AddComponentsScreen.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "GameEngine.h"

HMEngine::Core::WorldEditor::AddNormalGameObjectScreen::AddNormalGameObjectScreen(const glm::vec2& centerPos) :
	HMEngine::UI::Screen("scrnAddNormalGameObject", centerPos, glm::vec2(400, 650)),
	_btnGameObjectCategory(new HMEngine::UI::Button("btnGameObjectCategory", "./resources/UITextures/AddGameObjectReleased.png",
		"./resources/UITextures/AddGameObjectHovered.png", "./resources/UITextures/AddGameObjectPressed.png", glm::vec2(centerPos.x - 169, centerPos.y - 294),
		glm::vec2(50, 50), "", HMEngine::Fonts::ARIAL, glm::vec3())),
	_lblGameObjectName(new HMEngine::UI::Label("lblGameObjectName", glm::vec2(centerPos.x - 100, centerPos.y - 170),
		"Game object name:", HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtGameObjectName(new HMEngine::UI::TextBox("txtGameObjectName", glm::vec2(centerPos.x + 50, centerPos.y - 170), glm::vec2(120, 25),
		HMEngine::Fonts::ARIAL)),
	_lblGameObjectPositionTitle(new HMEngine::UI::Label("lblGameObjectPositionTitle", glm::vec2(centerPos.x - 89, centerPos.y - 130), "Game object position:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_lblGameObjectXPosition(new HMEngine::UI::Label("lblGameObjectXPosition", glm::vec2(centerPos.x - 170, centerPos.y - 105), "X:", HMEngine::Fonts::ARIAL,
		glm::vec3(), 0.8f)),
	_txtGameObjectXPosition(new HMEngine::UI::TextBox("txtGameObjectXPosition", glm::vec2(centerPos.x - 125, centerPos.y - 105), glm::vec2(65, 25), HMEngine::Fonts::ARIAL, false)),
	_lblGameObjectYPosition(new HMEngine::UI::Label("lblGameObjectYPosition", glm::vec2(centerPos.x - 60, centerPos.y - 105), "Y:", HMEngine::Fonts::ARIAL,
		glm::vec3(), 0.8f)),
	_txtGameObjectYPosition(new HMEngine::UI::TextBox("txtGameObjectYPosition", glm::vec2(centerPos.x - 15, centerPos.y - 105), glm::vec2(65, 25), HMEngine::Fonts::ARIAL, false)),
	_lblGameObjectZPosition(new HMEngine::UI::Label("lblGameObjectZPosition", glm::vec2(centerPos.x + 50, centerPos.y - 105), "Z:", HMEngine::Fonts::ARIAL,
		glm::vec3(), 0.8f)),
	_txtGameObjectZPosition(new HMEngine::UI::TextBox("txtGameObjectZPosition", glm::vec2(centerPos.x + 95, centerPos.y - 105), glm::vec2(65, 25), HMEngine::Fonts::ARIAL, false)),

	_lblGameObjectRotationTitle(new HMEngine::UI::Label("lblGameObjectRotationTitle", glm::vec2(centerPos.x - 89, centerPos.y - 80), "Game object rotation:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_lblGameObjectXRotation(new HMEngine::UI::Label("lblGameObjectXRotation", glm::vec2(centerPos.x - 170, centerPos.y - 55), "X:", HMEngine::Fonts::ARIAL,
		glm::vec3(), 0.8f)),
	_txtGameObjectXRotation(new HMEngine::UI::TextBox("txtGameObjectXRotation", glm::vec2(centerPos.x - 125, centerPos.y - 55), glm::vec2(65, 25), HMEngine::Fonts::ARIAL, false)),
	_lblGameObjectYRotation(new HMEngine::UI::Label("lblGameObjectYRotation", glm::vec2(centerPos.x - 60, centerPos.y - 55), "Y:", HMEngine::Fonts::ARIAL,
		glm::vec3(), 0.8f)),
	_txtGameObjectYRotation(new HMEngine::UI::TextBox("txtGameObjectYRotation", glm::vec2(centerPos.x - 15, centerPos.y - 55), glm::vec2(65, 25), HMEngine::Fonts::ARIAL, false)),
	_lblGameObjectZRotation(new HMEngine::UI::Label("lblGameObjectZRotation", glm::vec2(centerPos.x + 50, centerPos.y - 55), "Z:", HMEngine::Fonts::ARIAL,
		glm::vec3(), 0.8f)),
	_txtGameObjectZRotation(new HMEngine::UI::TextBox("txtGameObjectZRotation", glm::vec2(centerPos.x + 95, centerPos.y - 55), glm::vec2(65, 25), HMEngine::Fonts::ARIAL, false)),

	_lblGameObjectScaleTitle(new HMEngine::UI::Label("lblGameObjectScaleTitle", glm::vec2(centerPos.x - 89, centerPos.y - 30), "Game object scale:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_lblGameObjectXScale(new HMEngine::UI::Label("lblGameObjectXScale", glm::vec2(centerPos.x - 170, centerPos.y - 5), "X:", HMEngine::Fonts::ARIAL,
		glm::vec3(), 0.8f)),
	_txtGameObjectXScale(new HMEngine::UI::TextBox("txtGameObjectXScale", glm::vec2(centerPos.x - 125, centerPos.y - 5), glm::vec2(65, 25), HMEngine::Fonts::ARIAL, false)),
	_lblGameObjectYScale(new HMEngine::UI::Label("lblGameObjectYScale", glm::vec2(centerPos.x - 60, centerPos.y - 5), "Y:", HMEngine::Fonts::ARIAL,
		glm::vec3(), 0.8f)),
	_txtGameObjectYScale(new HMEngine::UI::TextBox("txtGameObjectYScale", glm::vec2(centerPos.x - 15, centerPos.y - 5), glm::vec2(65, 25), HMEngine::Fonts::ARIAL, false)),
	_lblGameObjectZScale(new HMEngine::UI::Label("lblGameObjectZScale", glm::vec2(centerPos.x + 50, centerPos.y - 5), "Z:", HMEngine::Fonts::ARIAL,
		glm::vec3(), 0.8f)),
	_txtGameObjectZScale(new HMEngine::UI::TextBox("txtGameObjectZScale", glm::vec2(centerPos.x + 95, centerPos.y - 5), glm::vec2(65, 25), HMEngine::Fonts::ARIAL, false)),

	_btnAddComponents(new HMEngine::UI::Button("btnAddComponents", "./resources/UITextures/NiceButtonReleased.png", "./resources/UITextures/NiceButtonHover.png",
		"./resources/UITextures/NiceButtonPressed.png", glm::vec2(centerPos.x, centerPos.y + 50), glm::vec2(120, 30), "Add Components", HMEngine::Fonts::ARIAL, glm::vec3())),
	_addComponentsScreen(new HMEngine::Core::WorldEditor::AddComponentsScreen(centerPos, std::bind(&AddNormalGameObjectScreen::AddComponent, this, std::placeholders::_1))),
	_btnAddGameObject(new HMEngine::UI::Button("btnAddGameObject", "./resources/UITextures/NiceButtonReleased.png", "./resources/UITextures/NiceButtonHover.png",
		"./resources/UITextures/NiceButtonPressed.png", glm::vec2(centerPos.x, centerPos.y + 100), glm::vec2(120, 30), "Add Game Object",
		HMEngine::Fonts::ARIAL, glm::vec3())),
	_lblErrorMsg(new HMEngine::UI::Label("lblErrorMsg", glm::vec2(centerPos.x, centerPos.y + 150), "SOME FIELDS ARE EMPTY!!",
		HMEngine::Fonts::ARIAL, glm::vec3(255, 0, 0), 1.0f)),
	_lblGameObjectNameErrorMsg(new HMEngine::UI::Label("lblGameObjectNameErrorMsg", glm::vec2(centerPos.x, centerPos.y + 160), "THIS NAME ALREADY EXISTS!",
		HMEngine::Fonts::ARIAL, glm::vec3(255, 0, 0), 1.0f))
{
	/* Sets the default values for the game object's transform details */
	this->_txtGameObjectXPosition->SetText("0");
	this->_txtGameObjectYPosition->SetText("0");
	this->_txtGameObjectZPosition->SetText("0");
	this->_txtGameObjectXRotation->SetText("0");
	this->_txtGameObjectYRotation->SetText("0");
	this->_txtGameObjectZRotation->SetText("0");
	this->_txtGameObjectXScale->SetText("1");
	this->_txtGameObjectYScale->SetText("1");
	this->_txtGameObjectZScale->SetText("1");

	/* Sets the onClick event of the add components button */
	*this->_btnAddComponents += [this](HMEngine::UI::Button* btn) { this->_addComponentsScreen->Show(); this->_lblErrorMsg->Hide(); };
	*this->_btnGameObjectCategory += [this](HMEngine::UI::Button* btn) { this->ShowNormalGameObjectSettings(); };
	*this->_btnAddGameObject += [this](HMEngine::UI::Button* btn)
	{
		if (this->_txtGameObjectXPosition->IsEmpty() || this->_txtGameObjectYPosition->IsEmpty() || this->_txtGameObjectZPosition->IsEmpty() ||
			this->_txtGameObjectXRotation->IsEmpty() || this->_txtGameObjectYRotation->IsEmpty() || this->_txtGameObjectZRotation->IsEmpty() ||
			this->_txtGameObjectXScale->IsEmpty() || this->_txtGameObjectYScale->IsEmpty() || this->_txtGameObjectZScale->IsEmpty() ||
			this->_txtGameObjectName->IsEmpty())
			this->_lblErrorMsg->Show();
		else
		{
			std::string gameObjectName = this->_txtGameObjectName->GetText();
			if (!this->_gameEngine->IsNameAvailable(gameObjectName))
			{
				this->_lblGameObjectNameErrorMsg->Show();
			}
			else
			{
				this->_lblGameObjectNameErrorMsg->Hide();
				float positionX = std::stof(this->_txtGameObjectXPosition->GetText());
				float positionY = std::stof(this->_txtGameObjectYPosition->GetText());
				float positionZ = std::stof(this->_txtGameObjectZPosition->GetText());
				float rotationX = std::stof(this->_txtGameObjectXRotation->GetText());
				float rotationY = std::stof(this->_txtGameObjectYRotation->GetText());
				float rotationZ = std::stof(this->_txtGameObjectZRotation->GetText());
				float scaleX = std::stof(this->_txtGameObjectXScale->GetText());
				float scaleY = std::stof(this->_txtGameObjectYScale->GetText());
				float scaleZ = std::stof(this->_txtGameObjectZScale->GetText());
				HMEngine::Core::GameObject* gameObject = new HMEngine::Core::GameObject(gameObjectName);
				gameObject->GetTransform().SetPosition(positionX, positionY, positionZ);
				gameObject->GetTransform().SetRotation(rotationX, rotationY, rotationZ);
				gameObject->GetTransform().SetScale(scaleX, scaleY, scaleZ);
				for (auto& component : this->_gameObjectComponents)
					gameObject->AddComponent(component);
				this->_gameEngine->AddGameObject(gameObject);
				this->_gameObjectComponents.clear();
			}
		}
	};
	this->AddQuad(this->_btnGameObjectCategory);
	this->AddQuad(this->_lblGameObjectName);
	this->AddQuad(this->_txtGameObjectName);

	this->AddQuad(this->_lblGameObjectPositionTitle);
	this->AddQuad(this->_lblGameObjectXPosition);
	this->AddQuad(this->_txtGameObjectXPosition);
	this->AddQuad(this->_lblGameObjectYPosition);
	this->AddQuad(this->_txtGameObjectYPosition);
	this->AddQuad(this->_lblGameObjectZPosition);
	this->AddQuad(this->_txtGameObjectZPosition);

	this->AddQuad(this->_lblGameObjectRotationTitle);
	this->AddQuad(this->_lblGameObjectXRotation);
	this->AddQuad(this->_txtGameObjectXRotation);
	this->AddQuad(this->_lblGameObjectYRotation);
	this->AddQuad(this->_txtGameObjectYRotation);
	this->AddQuad(this->_lblGameObjectZRotation);
	this->AddQuad(this->_txtGameObjectZRotation);

	this->AddQuad(this->_lblGameObjectScaleTitle);
	this->AddQuad(this->_lblGameObjectXScale);
	this->AddQuad(this->_txtGameObjectXScale);
	this->AddQuad(this->_lblGameObjectYScale);
	this->AddQuad(this->_txtGameObjectYScale);
	this->AddQuad(this->_lblGameObjectZScale);
	this->AddQuad(this->_txtGameObjectZScale);

	this->AddQuad(this->_btnAddGameObject);
	this->AddQuad(this->_btnAddComponents);

	this->AddQuad(this->_addComponentsScreen);

	this->AddQuad(this->_lblErrorMsg);
	this->AddQuad(this->_lblGameObjectNameErrorMsg);

	this->HideNormalGameObjectSettings();
}

HMEngine::Core::WorldEditor::AddNormalGameObjectScreen::~AddNormalGameObjectScreen()
{
}

void HMEngine::Core::WorldEditor::AddNormalGameObjectScreen::ShowEvent()
{
	this->_addComponentsScreen->Hide();
	this->HideNormalGameObjectSettings();
}

bool HMEngine::Core::WorldEditor::AddNormalGameObjectScreen::IsChildFocus() const
{
	return this->_addComponentsScreen->IsVisible() || this->IsVisible();
}

void HMEngine::Core::WorldEditor::AddNormalGameObjectScreen::ShowNormalGameObjectSettings()
{
	this->_lblGameObjectName->Show();
	this->_txtGameObjectName->Show();
	this->_lblGameObjectPositionTitle->Show();
	this->_lblGameObjectXPosition->Show();
	this->_txtGameObjectXPosition->Show();
	this->_lblGameObjectYPosition->Show();
	this->_txtGameObjectYPosition->Show();
	this->_lblGameObjectZPosition->Show();
	this->_txtGameObjectZPosition->Show();
	this->_lblGameObjectRotationTitle->Show();
	this->_lblGameObjectXRotation->Show();
	this->_txtGameObjectXRotation->Show();
	this->_lblGameObjectYRotation->Show();
	this->_txtGameObjectYRotation->Show();
	this->_lblGameObjectZRotation->Show();
	this->_txtGameObjectZRotation->Show();
	this->_lblGameObjectScaleTitle->Show();
	this->_lblGameObjectXScale->Show();
	this->_txtGameObjectXScale->Show();
	this->_lblGameObjectYScale->Show();
	this->_txtGameObjectYScale->Show();
	this->_lblGameObjectZScale->Show();
	this->_txtGameObjectZScale->Show();
	this->_btnAddComponents->Show();
	this->_btnAddGameObject->Show();
}

void HMEngine::Core::WorldEditor::AddNormalGameObjectScreen::HideNormalGameObjectSettings()
{
	this->_lblGameObjectName->Hide();
	this->_txtGameObjectName->Hide();
	this->_lblGameObjectPositionTitle->Hide();
	this->_lblGameObjectXPosition->Hide();
	this->_txtGameObjectXPosition->Hide();
	this->_lblGameObjectYPosition->Hide();
	this->_txtGameObjectYPosition->Hide();
	this->_lblGameObjectZPosition->Hide();
	this->_txtGameObjectZPosition->Hide();
	this->_lblGameObjectRotationTitle->Hide();
	this->_lblGameObjectXRotation->Hide();
	this->_txtGameObjectXRotation->Hide();
	this->_lblGameObjectYRotation->Hide();
	this->_txtGameObjectYRotation->Hide();
	this->_lblGameObjectZRotation->Hide();
	this->_txtGameObjectZRotation->Hide();
	this->_lblGameObjectScaleTitle->Hide();
	this->_lblGameObjectXScale->Hide();
	this->_txtGameObjectXScale->Hide();
	this->_lblGameObjectYScale->Hide();
	this->_txtGameObjectYScale->Hide();
	this->_lblGameObjectZScale->Hide();
	this->_txtGameObjectZScale->Hide();
	this->_btnAddComponents->Hide();
	this->_btnAddGameObject->Hide();
	this->_lblErrorMsg->Hide();
	this->_lblGameObjectNameErrorMsg->Hide();
}

void HMEngine::Core::WorldEditor::AddNormalGameObjectScreen::AddComponent(HMEngine::Components::Component* component)
{
	this->_gameObjectComponents.push_back(component);
	this->_addComponentsScreen->Hide();
}