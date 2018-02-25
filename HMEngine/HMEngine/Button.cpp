#include "Button.h"
#include "HardwareInputs.h"
#include "Label.h"
#include "Font.h"
#include <iostream>
#include "GameEngine.h"

HMEngine::UI::Button::Button(const std::string& name, const std::string& buttonReleasedTexture, const std::string& buttonHoverTexture,
	const std::string& buttonPressedTexture, const glm::vec2& position, const glm::vec2& scale, const std::string& labelText, const HMEngine::UI::Font& font,
	const glm::vec3& labelTextColor, float labelFontSize) : HMEngine::UI::Quad(name, buttonReleasedTexture, position, scale), 
	_buttonReleasedTexture(buttonReleasedTexture), _buttonPressedTexture(buttonPressedTexture),  
	_label(new HMEngine::UI::Label(name + "_button_label", position, scale, labelText, font, labelTextColor))
{
	this->AddTexture(buttonHoverTexture);
	this->AddTexture(buttonPressedTexture);
}

HMEngine::UI::Button::~Button()
{
}

HMEngine::UI::Button::Button(const HMEngine::UI::Button& other) : HMEngine::UI::Quad(other), _buttonReleasedTexture(other._buttonReleasedTexture),
_buttonPressedTexture(other._buttonPressedTexture)
{
	this->_label = new HMEngine::UI::Label(*other._label);
}

HMEngine::UI::Button& HMEngine::UI::Button::operator=(const HMEngine::UI::Button& other)
{
	if (this != &other)
	{
		HMEngine::UI::Quad::operator=(other);
		delete this->_label;
		this->_label = new HMEngine::UI::Label(*other._label);
		this->_buttonReleasedTexture = other._buttonReleasedTexture;
		this->_buttonPressedTexture = other._buttonPressedTexture;
	}

	return *this;
}

void HMEngine::UI::Button::Update()
{
	if (HMEngine::Core::Hardware::HardwareInputs::IsCursorWithinBoundaries(this->_quadDetails.topLeft, this->_quadDetails.bottomRight))
	{
		if (HMEngine::Core::Hardware::HardwareInputs::IsMouseButtonDown(SDL_BUTTON_LEFT))
		{
			this->SetTexture(this->BUTTON_PRESSED);
		}
		else
		{
			this->SetTexture(this->BUTTON_HOVER);
		}
	}
	else
	{
		this->SetTexture(this->BUTTON_RELEASED);
	}
}

void HMEngine::UI::Button::AttachToGameEngineEvent(HMEngine::GameEngine& gameEngine)
{
	gameEngine.AddUI(this->_label);
}