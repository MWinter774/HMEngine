#include "AddNormalGameObjectScreen.h"
#include "QuadCollection.h"
#include "TextBox.h"
#include "Button.h"
#include "Label.h"
#include "Fonts.h"
#include "GameEngine.h"
#include "AddComponentsScreen.h"

HMEngine::Core::WorldEditor::AddNormalGameObjectScreen::AddNormalGameObjectScreen(const glm::vec2& centerPos) :
	HMEngine::UI::Screen("scrnAddNormalGameObject", centerPos, glm::vec2(400, 650)),
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
		"./resources/UITextures/NiceButtonPressed.png", glm::vec2(centerPos.x, centerPos.y + 50), glm::vec2(120, 30), "Add Components", HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_addComponentsScreen(new HMEngine::Core::WorldEditor::AddComponentsScreen(centerPos))
{
	/* Sets the default values for the game object's transform details */
	this->_txtGameObjectXRotation->SetText("0");
	this->_txtGameObjectYRotation->SetText("0");
	this->_txtGameObjectZRotation->SetText("0");
	this->_txtGameObjectXScale->SetText("1");
	this->_txtGameObjectYScale->SetText("1");
	this->_txtGameObjectZScale->SetText("1");

	/* Sets the onClick event of the add components button */
	*this->_btnAddComponents += [this](HMEngine::UI::Button* btn) { this->_addComponentsScreen->Show(); };

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

	this->AddQuad(this->_btnAddComponents);

	this->AddQuad(this->_addComponentsScreen);
}

HMEngine::Core::WorldEditor::AddNormalGameObjectScreen::~AddNormalGameObjectScreen()
{
}

void HMEngine::Core::WorldEditor::AddNormalGameObjectScreen::HideEvent()
{
}

void HMEngine::Core::WorldEditor::AddNormalGameObjectScreen::ShowEvent()
{
	this->_addComponentsScreen->Hide();
}