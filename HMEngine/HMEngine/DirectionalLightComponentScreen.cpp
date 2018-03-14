#include "DirectionalLightComponentScreen.h"
#include "Label.h"
#include "TextBox.h"
#include "Fonts.h"
#include "Button.h"
#include "DirectionalLight.h"

HMEngine::Core::WorldEditor::ComponentScreens::DirectionalLightComponentScreen::DirectionalLightComponentScreen(const glm::vec2& centerPos) :
	HMEngine::UI::Screen("scrnDirectionalLightComponent", centerPos, glm::vec2(400, 250)),
	_lblTitle(new HMEngine::UI::Label(this->_name + "_lblTitle", glm::vec2(centerPos.x, centerPos.y - 105), "Directional Light", HMEngine::Fonts::ARIAL, glm::vec3(), 1.2f)),
	_lblColorTitle(new HMEngine::UI::Label(this->_name + "_lblColorTitle", glm::vec2(centerPos.x - 160, centerPos.y - 85), "Color:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_lblColorR(new HMEngine::UI::Label(this->_name + "_lblColorR", glm::vec2(centerPos.x - 175, centerPos.y - 60), "R:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtColorR(new HMEngine::UI::TextBox(this->_name + "_txtColorR", glm::vec2(centerPos.x - 120, centerPos.y - 60), glm::vec2(90, 25),
		HMEngine::Fonts::ARIAL, false)),
	_lblColorG(new HMEngine::UI::Label(this->_name + "_lblColorG", glm::vec2(centerPos.x - 55, centerPos.y - 60), "G:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtColorG(new HMEngine::UI::TextBox(this->_name + "_txtColorG", glm::vec2(centerPos.x + 5, centerPos.y - 60), glm::vec2(90, 25), HMEngine::Fonts::ARIAL, false)),
	_lblColorB(new HMEngine::UI::Label(this->_name + "_lblColorB", glm::vec2(centerPos.x + 70, centerPos.y - 60), "B:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtColorB(new HMEngine::UI::TextBox(this->_name + "_txtColorB", glm::vec2(centerPos.x + 130, centerPos.y - 60), glm::vec2(90, 25), HMEngine::Fonts::ARIAL, false)),
	_lblIntensityTitle(new HMEngine::UI::Label(this->_name + "_lblIntensityTitle", glm::vec2(centerPos.x - 148, centerPos.y - 25), "Intensity:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtIntensity(new HMEngine::UI::TextBox(this->_name + "_txtIntensity", glm::vec2(centerPos.x - 65, centerPos.y - 25), glm::vec2(90, 25),
		HMEngine::Fonts::ARIAL, false)),
	_lblDirectionTitle(new HMEngine::UI::Label(this->_name + "_lblDirectionTitle", glm::vec2(centerPos.x - 147, centerPos.y), "Direction:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_lblDirectionX(new HMEngine::UI::Label(this->_name + "_lblDirectionX", glm::vec2(centerPos.x - 175, centerPos.y + 25), "X:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtDirectionX(new HMEngine::UI::TextBox(this->_name + "_txtDirectionX", glm::vec2(centerPos.x - 120, centerPos.y + 25), glm::vec2(90, 25),
		HMEngine::Fonts::ARIAL, false)),
	_lblDirectionY(new HMEngine::UI::Label(this->_name + "_lblDirectionY", glm::vec2(centerPos.x - 55, centerPos.y + 25), "Y:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtDirectionY(new HMEngine::UI::TextBox(this->_name + "_txtDirectionY", glm::vec2(centerPos.x + 5, centerPos.y + 25), glm::vec2(90, 25),
		HMEngine::Fonts::ARIAL, false)),
	_lblDirectionZ(new HMEngine::UI::Label(this->_name + "_lblDirectionZ", glm::vec2(centerPos.x + 70, centerPos.y + 25), "Z:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtDirectionZ(new HMEngine::UI::TextBox(this->_name + "_txtDirectionZ", glm::vec2(centerPos.x + 130, centerPos.y + 25), glm::vec2(90, 25),
		HMEngine::Fonts::ARIAL, false)),
	_btnAddComponent(new HMEngine::UI::Button(this->_name + "_btnAddComponent", "./resources/UITextures/NiceButtonReleased.png",
		"./resources/UITextures/NiceButtonHover.png", "./resources/UITextures/NiceButtonPressed.png", glm::vec2(centerPos.x, centerPos.y + 95),
		glm::vec2(120, 40), "Add Component", HMEngine::Fonts::ARIAL, glm::vec3())),
	_lblError(new HMEngine::UI::Label(this->_name + "_lblError", glm::vec2(centerPos.x, centerPos.y + 60), "SOME FIELDS ARE EMPTY!!",
		HMEngine::Fonts::ARIAL, glm::vec3(255, 0, 0), 1.0f))
{
	*this->_btnAddComponent += [this](HMEngine::UI::Button* btn)
	{
		if (this->_txtColorR->IsEmpty() || this->_txtColorG->IsEmpty() || this->_txtColorB->IsEmpty() || this->_txtIntensity->IsEmpty() ||
			this->_txtDirectionX->IsEmpty() || this->_txtDirectionY->IsEmpty() || this->_txtDirectionZ->IsEmpty())
		{
			this->_lblError->Show();
		}
		else
		{
			this->_lblError->Hide();
			float r = std::stof(this->_txtColorR->GetText());
			float g = std::stof(this->_txtColorG->GetText());
			float b = std::stof(this->_txtColorB->GetText());
			float intensity = std::stof(this->_txtIntensity->GetText());
			float x = std::stof(this->_txtDirectionX->GetText());
			float y = std::stof(this->_txtDirectionY->GetText());
			float z = std::stof(this->_txtDirectionZ->GetText());
			this->_addComponentEvent(new HMEngine::Components::DirectionalLight(HMEngine::Components::BaseLight(glm::vec3(r, g, b), intensity), 
				glm::vec3(x, y, z)));
		}
	};

	this->SetBackground("./resources/UITextures/AddGameObjectMenu.png");
	this->AddQuad(this->_lblTitle);
	this->AddQuad(this->_lblColorTitle);
	this->AddQuad(this->_lblColorR);
	this->AddQuad(this->_txtColorR);
	this->AddQuad(this->_lblColorG);
	this->AddQuad(this->_txtColorG);
	this->AddQuad(this->_lblColorB);
	this->AddQuad(this->_txtColorB);
	this->AddQuad(this->_lblIntensityTitle);
	this->AddQuad(this->_txtIntensity);
	this->AddQuad(this->_lblDirectionTitle);
	this->AddQuad(this->_lblDirectionX);
	this->AddQuad(this->_txtDirectionX);
	this->AddQuad(this->_lblDirectionY);
	this->AddQuad(this->_txtDirectionY);
	this->AddQuad(this->_lblDirectionZ);
	this->AddQuad(this->_txtDirectionZ);
	this->AddQuad(this->_btnAddComponent);
	this->AddQuad(this->_lblError);

	this->Hide();
}

HMEngine::Core::WorldEditor::ComponentScreens::DirectionalLightComponentScreen::~DirectionalLightComponentScreen()
{
}

void HMEngine::Core::WorldEditor::ComponentScreens::DirectionalLightComponentScreen::ShowEvent()
{
	this->_lblError->Hide();
}