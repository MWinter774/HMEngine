#include "Button.h"
#include "HardwareInputs.h"
#include <iostream>

HMEngine::UI::Button::Button(const std::string& name, const std::string& buttonReleasedTexture, const std::string& buttonHoverTexture, 
	const std::string& buttonPressedTexture, const glm::vec2& position, const glm::vec2& scale) : HMEngine::UI::Quad(name, buttonReleasedTexture, position, scale), 
	_buttonReleasedTexture(buttonReleasedTexture), _buttonPressedTexture(buttonPressedTexture)
{
	this->AddTexture(buttonHoverTexture);
	this->AddTexture(buttonPressedTexture);
}

HMEngine::UI::Button::~Button()
{
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