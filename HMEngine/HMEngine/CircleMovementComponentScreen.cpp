#include "CircleMovementComponentScreen.h"
#include "Label.h"
#include "TextBox.h"
#include "Fonts.h"
#include "Button.h"
#include "CircleMovement.h"

HMEngine::Core::WorldEditor::ComponentScreens::CircleMovementComponentScreen::CircleMovementComponentScreen(const glm::vec2& centerPos) :
	HMEngine::UI::Screen("scrnCircleMovementComponent", centerPos, glm::vec2(400, 200)),
	_lblTitle(new HMEngine::UI::Label(this->_name + "_lblTitle", glm::vec2(centerPos.x, centerPos.y - 80), "Circle Movement", HMEngine::Fonts::ARIAL, glm::vec3(), 1.2f)),
	_lblCircleCenterTitle(new HMEngine::UI::Label(this->_name + "_lblCircleCenterTitle", glm::vec2(centerPos.x - 150, centerPos.y - 60), "Center:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_lblXCenter(new HMEngine::UI::Label(this->_name + "_lblXCenter", glm::vec2(centerPos.x - 170, centerPos.y - 35), "X:", HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtXCenter(new HMEngine::UI::TextBox(this->_name + "_txtXCenter", glm::vec2(centerPos.x - 110, centerPos.y - 35), glm::vec2(100, 20), HMEngine::Fonts::ARIAL, false)),
	_lblYCenter(new HMEngine::UI::Label(this->_name + "_lblYCenter", glm::vec2(centerPos.x - 40, centerPos.y - 35), "Y:", HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtYCenter(new HMEngine::UI::TextBox(this->_name + "_txtYCenter", glm::vec2(centerPos.x + 20, centerPos.y - 35), glm::vec2(100, 20), HMEngine::Fonts::ARIAL, false)),
	_lblRadius(new HMEngine::UI::Label(this->_name + "_lblRadius", glm::vec2(centerPos.x - 148, centerPos.y - 5), "Radius:", HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtRadius(new HMEngine::UI::TextBox(this->_name + "_txtRadius", glm::vec2(centerPos.x - 65, centerPos.y - 5), glm::vec2(100, 20), HMEngine::Fonts::ARIAL, false)),
	_btnAddComponent(new HMEngine::UI::Button(this->_name + "_btnAddComponent", "./resources/UITextures/NiceButtonReleased.png",
		"./resources/UITextures/NiceButtonHover.png", "./resources/UITextures/NiceButtonPressed.png", glm::vec2(centerPos.x, centerPos.y + 70),
		glm::vec2(120, 40), "Add Component", HMEngine::Fonts::ARIAL, glm::vec3())),
	_lblError(new HMEngine::UI::Label(this->_name + "_lblError", glm::vec2(centerPos.x, centerPos.y + 30), "SOME FIELDS ARE EMPTY!!",
		HMEngine::Fonts::ARIAL, glm::vec3(255, 0, 0), 1.0f))
{
	*this->_btnAddComponent += [this](HMEngine::UI::Button* btn)
	{
		if (this->_txtRadius->IsEmpty() || this->_txtXCenter->IsEmpty() || this->_txtYCenter->IsEmpty())
		{
			this->_lblError->Show();
		}
		else
		{
			this->_lblError->Hide();
			float centerX = std::stof(this->_txtXCenter->GetText());
			float centerY = std::stof(this->_txtYCenter->GetText());
			float radius = std::stof(this->_txtRadius->GetText());
			this->_addComponentEvent(new HMEngine::Components::CircleMovement(centerX, centerY, radius));
		}
	};

	this->SetBackground("./resources/UITextures/AddGameObjectMenu.png");
	this->AddQuad(this->_lblCircleCenterTitle);
	this->AddQuad(this->_lblRadius);
	this->AddQuad(this->_lblTitle);
	this->AddQuad(this->_lblXCenter);
	this->AddQuad(this->_lblYCenter);
	this->AddQuad(this->_txtRadius);
	this->AddQuad(this->_txtXCenter);
	this->AddQuad(this->_txtYCenter);
	this->AddQuad(this->_btnAddComponent);
	this->AddQuad(this->_lblError);

	this->Hide();
}

HMEngine::Core::WorldEditor::ComponentScreens::CircleMovementComponentScreen::~CircleMovementComponentScreen()
{
}

void HMEngine::Core::WorldEditor::ComponentScreens::CircleMovementComponentScreen::ShowEvent()
{
	this->_lblError->Hide();
}