#include "PointLightComponentScreen.h"
#include "Label.h"
#include "Fonts.h"
#include "TextBox.h"
#include "Button.h"
#include "PointLight.h"

HMEngine::Core::WorldEditor::ComponentScreens::PointLightComponentScreen::PointLightComponentScreen(const glm::vec2& centerPos) :
	HMEngine::UI::Screen("scrnPointLightComponent", centerPos, glm::vec2(450, 350)),
	_lblTitle(new HMEngine::UI::Label(this->_name + "_lblTitle", glm::vec2(centerPos.x, centerPos.y - 140), "Point Light", HMEngine::Fonts::ARIAL, glm::vec3(), 1.2f)),
	_lblColorTitle(new HMEngine::UI::Label(this->_name + "_lblColorTitle", glm::vec2(centerPos.x - 160, centerPos.y - 120), "Color:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_lblColorR(new HMEngine::UI::Label(this->_name + "_lblColorR", glm::vec2(centerPos.x - 175, centerPos.y - 95), "R:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtColorR(new HMEngine::UI::TextBox(this->_name + "_txtColorR", glm::vec2(centerPos.x - 120, centerPos.y - 95), glm::vec2(90, 25),
		HMEngine::Fonts::ARIAL, false)),
	_lblColorG(new HMEngine::UI::Label(this->_name + "_lblColorG", glm::vec2(centerPos.x - 55, centerPos.y - 95), "G:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtColorG(new HMEngine::UI::TextBox(this->_name + "_txtColorG", glm::vec2(centerPos.x + 5, centerPos.y - 95), glm::vec2(90, 25), HMEngine::Fonts::ARIAL, false)),
	_lblColorB(new HMEngine::UI::Label(this->_name + "_lblColorB", glm::vec2(centerPos.x + 70, centerPos.y - 95), "B:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtColorB(new HMEngine::UI::TextBox(this->_name + "_txtColorB", glm::vec2(centerPos.x + 130, centerPos.y - 95), glm::vec2(90, 25), HMEngine::Fonts::ARIAL, false)),
	_lblIntensityTitle(new HMEngine::UI::Label(this->_name + "_lblIntensityTitle", glm::vec2(centerPos.x - 148, centerPos.y - 60), "Intensity:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtIntensity(new HMEngine::UI::TextBox(this->_name + "_txtIntensity", glm::vec2(centerPos.x - 65, centerPos.y - 60), glm::vec2(90, 25),
		HMEngine::Fonts::ARIAL, false)),
	_lblAttenuationTitle(new HMEngine::UI::Label(this->_name + "_lblAttenuationTitle", glm::vec2(centerPos.x - 137, centerPos.y - 25), "Attenuation:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_lblAttenuationX(new HMEngine::UI::Label(this->_name + "_lblAttenuationX", glm::vec2(centerPos.x - 175, centerPos.y), "X:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtAttenuationX(new HMEngine::UI::TextBox(this->_name + "_txtAttenuationX", glm::vec2(centerPos.x - 120, centerPos.y), glm::vec2(90, 25),
		HMEngine::Fonts::ARIAL, false)),
	_lblAttenuationY(new HMEngine::UI::Label(this->_name + "_lblAttenuationY", glm::vec2(centerPos.x - 55, centerPos.y), "Y:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtAttenuationY(new HMEngine::UI::TextBox(this->_name + "_txtAttenuationY", glm::vec2(centerPos.x + 5, centerPos.y), glm::vec2(90, 25),
		HMEngine::Fonts::ARIAL, false)),
	_lblAttenuationZ(new HMEngine::UI::Label(this->_name + "_lblAttenuationZ", glm::vec2(centerPos.x + 70, centerPos.y), "Z:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtAttenuationZ(new HMEngine::UI::TextBox(this->_name + "_txtAttenuationZ", glm::vec2(centerPos.x + 130, centerPos.y), glm::vec2(90, 25),
		HMEngine::Fonts::ARIAL, false)),
	_lblRange(new HMEngine::UI::Label(this->_name + "_lblRange", glm::vec2(centerPos.x - 155, centerPos.y + 30), "Range:",
		HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f)),
	_txtRange(new HMEngine::UI::TextBox(this->_name + "_txtRange", glm::vec2(centerPos.x - 80, centerPos.y + 30), glm::vec2(90, 25),
		HMEngine::Fonts::ARIAL, false)),
	_btnAddComponent(new HMEngine::UI::Button(this->_name + "_btnAddComponent", "./resources/UITextures/NiceButtonReleased.png",
		"./resources/UITextures/NiceButtonHover.png", "./resources/UITextures/NiceButtonPressed.png", glm::vec2(centerPos.x, centerPos.y + 120),
		glm::vec2(120, 40), "Add Component", HMEngine::Fonts::ARIAL, glm::vec3())),
	_lblError(new HMEngine::UI::Label(this->_name + "_lblError", glm::vec2(centerPos.x, centerPos.y + 80), "SOME FIELDS ARE EMPTY!!",
		HMEngine::Fonts::ARIAL, glm::vec3(255, 0, 0), 1.0f))
{
	*this->_btnAddComponent += [this](HMEngine::UI::Button* btn)
	{
		if (this->_txtColorR->IsEmpty() || this->_txtColorG->IsEmpty() || this->_txtColorB->IsEmpty() || this->_txtIntensity->IsEmpty() ||
			this->_txtAttenuationX->IsEmpty() || this->_txtAttenuationY->IsEmpty() || this->_txtAttenuationZ->IsEmpty() || this->_txtRange->IsEmpty())
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
			float x = std::stof(this->_txtAttenuationX->GetText());
			float y = std::stof(this->_txtAttenuationY->GetText());
			float z = std::stof(this->_txtAttenuationZ->GetText());
			float range = std::stof(this->_txtRange->GetText());
			this->_addComponentEvent(new HMEngine::Components::PointLight(HMEngine::Components::BaseLight(glm::vec3(r, g, b), intensity),
				glm::vec3(x, y, z), range));
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
	this->AddQuad(this->_lblAttenuationTitle);
	this->AddQuad(this->_lblAttenuationX);
	this->AddQuad(this->_txtAttenuationX);
	this->AddQuad(this->_lblAttenuationY);
	this->AddQuad(this->_txtAttenuationY);
	this->AddQuad(this->_lblAttenuationZ);
	this->AddQuad(this->_txtAttenuationZ);
	this->AddQuad(this->_lblRange);
	this->AddQuad(this->_txtRange);
	this->AddQuad(this->_lblError);
	this->AddQuad(this->_btnAddComponent);
	this->Hide();
}

HMEngine::Core::WorldEditor::ComponentScreens::PointLightComponentScreen::~PointLightComponentScreen()
{
}

void HMEngine::Core::WorldEditor::ComponentScreens::PointLightComponentScreen::ShowEvent()
{
	this->_lblError->Hide();
}