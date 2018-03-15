#include "Button.h"
#include "HardwareInputs.h"
#include "Label.h"
#include "Font.h"
#include <iostream>
#include "GameEngine.h"

HMEngine::UI::Button::Button(const std::string& name, const std::string& buttonReleasedTexture, const std::string& buttonHoverTexture,
	const std::string& buttonPressedTexture, const glm::vec2& position, const glm::vec2& scale, const std::string& labelText, const HMEngine::UI::Font& font,
	const glm::vec3& labelTextColor) : HMEngine::UI::Quad(name, buttonReleasedTexture, position, scale),
	_buttonReleasedTexture(buttonReleasedTexture), _buttonPressedTexture(buttonPressedTexture), _state(this->BUTTON_RELEASED),
	_label(new HMEngine::UI::Label(name + "_button_label", position, scale, labelText, font, labelTextColor)), _onClickEvents() 
{
	this->InitializeEvents<Button>(this);

	this->AddTexture(buttonHoverTexture);
	this->AddTexture(buttonPressedTexture);
	this->AddChild(this->_label);
}

HMEngine::UI::Button::Button(const std::string& name, const std::string& buttonReleasedTexture, const std::string& buttonHoverTexture,
	const std::string& buttonPressedTexture, const glm::vec2& position, const glm::vec2& scale, const std::string& labelText, const HMEngine::UI::Font& font,
	const glm::vec3& labelTextColor, float labelFontSize) : HMEngine::UI::Quad(name, buttonReleasedTexture, position, scale),
	_buttonReleasedTexture(buttonReleasedTexture), _buttonPressedTexture(buttonPressedTexture), _state(this->BUTTON_RELEASED),
	_label(new HMEngine::UI::Label(name + "_button_label", position, labelText, font, labelTextColor, labelFontSize)), _onClickEvents()
{
	this->InitializeEvents<Button>(this);

	this->AddTexture(buttonHoverTexture);
	this->AddTexture(buttonPressedTexture);
	this->AddChild(this->_label);
}

HMEngine::UI::Button::~Button()
{
}

HMEngine::UI::Button::Button(const HMEngine::UI::Button& other) : HMEngine::UI::Quad(other), _buttonReleasedTexture(other._buttonReleasedTexture),
_buttonPressedTexture(other._buttonPressedTexture), _state(this->BUTTON_RELEASED), _onClickEvents(other._onClickEvents)
{
	this->InitializeEvents<Button>(this);

	this->_label = new HMEngine::UI::Label(*other._label);
}

HMEngine::UI::Button& HMEngine::UI::Button::operator=(const HMEngine::UI::Button& other)
{
	if (this != &other)
	{
		this->InitializeEvents<Button>(this);
		HMEngine::UI::Quad::operator=(other);

		this->_label = new HMEngine::UI::Label(*other._label);
		this->_buttonReleasedTexture = other._buttonReleasedTexture;
		this->_buttonPressedTexture = other._buttonPressedTexture;
		this->_state = this->BUTTON_RELEASED;
		this->_onClickEvents = other._onClickEvents;
	}

	return *this;
}

void HMEngine::UI::Button::operator+=(const std::function<void(HMEngine::UI::Button*)>& onClickEvent)
{
	this->_onClickEvents.push_back(onClickEvent);
}

void HMEngine::UI::Button::UpdateEvent()
{
	if (this->_state != this->BUTTON_PRESSED && HMEngine::Core::Hardware::HardwareInputs::IsCursorWithinBoundaries(this->_quadDetails.topLeft, this->_quadDetails.bottomRight))
	{
		this->SetTexture(this->_state = this->BUTTON_HOVER);
	}
	else if (this->_state != this->BUTTON_RELEASED)
	{
		this->SetTexture(this->_state = this->BUTTON_RELEASED);
	}
}

void HMEngine::UI::Button::MouseButtonTappedEvent(const unsigned int& mouseButton)
{
	if (mouseButton == SDL_BUTTON_LEFT && HMEngine::Core::Hardware::HardwareInputs::IsCursorWithinBoundaries(this->_quadDetails.topLeft, this->_quadDetails.bottomRight))
	{
		this->SetTexture(this->_state = this->BUTTON_PRESSED);
		for (auto& onClickEvent : this->_onClickEvents)
		{
			onClickEvent(this);
		}
	}
}

void HMEngine::UI::Button::SetTextToTopLeft()
{
	this->_label->SetTopLeft(this->GetTopLeft());
}
