#include "AddComponentsScreen.h"
#include "GameEngine.h"
#include "Label.h"
#include "Fonts.h"
#include "TextBox.h"
#include "List.h"

HMEngine::Core::WorldEditor::AddComponentsScreen::AddComponentsScreen(const glm::vec2& centerPos) :
	HMEngine::UI::Screen("scrnAddComponents", centerPos, glm::vec2(500, 300)),
	_lblAddComponentsTitle(new HMEngine::UI::Label("lblAddComponentsTitle", glm::vec2(centerPos.x, centerPos.y-130), "Add Components", HMEngine::Fonts::ARIAL, 
		glm::vec3(), 1.0f)),
	_txtComponentSearch(new HMEngine::UI::TextBox("txtComponentSerach", glm::vec2(centerPos.x, centerPos.y-90), glm::vec2(400, 25), HMEngine::Fonts::ARIAL)),
	_lstComponentsList(new HMEngine::UI::List("lstComponentsList", glm::vec2(centerPos.x, centerPos.y+30), glm::vec2(400, 200), "./resources/UITextures/listBackground.png"))
{
	this->_lstComponentsList->AddButton("MeshRenderer", [](HMEngine::UI::Button* btn) {});
	this->_lstComponentsList->AddButton("CircleMovement", [](HMEngine::UI::Button* btn) {});

	this->SetBackground("./resources/UITextures/AddGameObjectMenu.png");
	this->AddChild(this->_lblAddComponentsTitle);
	this->AddChild(this->_txtComponentSearch);
	this->AddChild(this->_lstComponentsList);
	this->Hide();
}

HMEngine::Core::WorldEditor::AddComponentsScreen::~AddComponentsScreen()
{
}