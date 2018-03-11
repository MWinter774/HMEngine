#include "MeshRendererComponentScreen.h"
#include "TextBox.h"
#include "Fonts.h"

HMEngine::Core::WorldEditor::ComponentScreens::MeshRendererComponentScreen::MeshRendererComponentScreen(const glm::vec2& centerPos) :
	HMEngine::UI::Screen("scrnMeshRenderer", centerPos, glm::vec2(600, 600)),
	_txtObjFilePath(new HMEngine::UI::TextBox(this->_name + "_txtObjFilePath", glm::vec2(centerPos), glm::vec2(105, 25), HMEngine::Fonts::ARIAL)),
	_txtTextureFilePath(new HMEngine::UI::TextBox(this->_name + "_txtTextureFilePath", glm::vec2(centerPos.x, centerPos.y + 40), glm::vec2(105, 25),
		HMEngine::Fonts::ARIAL))
{
	this->SetBackground("./resources/UITextures/AddGameObjectMenu.png");
	this->AddChild(this->_txtObjFilePath);
	this->AddChild(this->_txtTextureFilePath);

	this->_txtObjFilePath->Hide();
	this->_txtTextureFilePath->Hide();
}

HMEngine::Core::WorldEditor::ComponentScreens::MeshRendererComponentScreen::~MeshRendererComponentScreen()
{
}