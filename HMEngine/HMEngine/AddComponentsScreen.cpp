#include "AddComponentsScreen.h"
#include "GameEngine.h"
#include "Menu.h"

HMEngine::Core::WorldEditor::AddComponentsScreen::AddComponentsScreen(const glm::vec2& centerPos) :
	HMEngine::UI::Menu("scrnAddComponents", centerPos, glm::vec2(500, 300), "./resources/UITextures/AddGameObjectMenu.png")
{
	this->Hide();
}

HMEngine::Core::WorldEditor::AddComponentsScreen::~AddComponentsScreen()
{
}

//void HMEngine::Core::WorldEditor::AddComponentsScreen::Show()
//{
//	this->Show();
//}
//
//void HMEngine::Core::WorldEditor::AddComponentsScreen::Hide()
//{
//	this->Hide();
//}

void HMEngine::Core::WorldEditor::AddComponentsScreen::AddToGameEngine(HMEngine::GameEngine& gameEngine)
{
	//gameEngine.AddUI(this->_screen);
}

//void HMEngine::Core::WorldEditor::AddComponentsScreen::BringToFront()
//{
//	this->BringToFront();
//}
