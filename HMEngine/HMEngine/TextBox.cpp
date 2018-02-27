#include "TextBox.h"
#include "Label.h"
#include "GameEngine.h"
#include "HardwareInputs.h"

HMEngine::UI::TextBox::TextBox(const std::string& name, const glm::vec2& position, const glm::vec2& scale, const HMEngine::UI::Font& font) :
	HMEngine::UI::Quad(name, "./resources/UITextures/TextBoxUnfocused.png", position, scale),
	_label(new HMEngine::UI::Label(name + "_textbox_label", position, scale, "", font, { 0,0,0 })), _isFocused(false)
{
	this->InitializeEvents<TextBox>(this);
	this->AddTexture("./resources/UITextures/TextBoxFocused.png");
}

HMEngine::UI::TextBox::~TextBox()
{
}

HMEngine::UI::TextBox::TextBox(const HMEngine::UI::TextBox& other) : HMEngine::UI::Quad(other), _label(new HMEngine::UI::Label(*other._label)), _isFocused(false)
{
	this->InitializeEvents<TextBox>(this);
}

HMEngine::UI::TextBox& HMEngine::UI::TextBox::operator=(const HMEngine::UI::TextBox& other)
{
	if (this != &other)
	{
		HMEngine::UI::Quad::operator=(other);
		this->_label = new HMEngine::UI::Label(*other._label);
		this->InitializeEvents<TextBox>(this);
		this->_isFocused = false;
	}

	return *this;
}

void HMEngine::UI::TextBox::UpdateEvent()
{
	/*if (HMEngine::Core::Hardware::HardwareInputs::IsCursorWithinBoundaries(this->_quadDetails.topLeft, this->_quadDetails.bottomRight))
	{
		if (HMEngine::Core::Hardware::HardwareInputs::IsMouseButtonDown(SDL_BUTTON_LEFT))
		{
			this->SetTexture(1);
		}
	}
	else if (HMEngine::Core::Hardware::HardwareInputs::IsMouseButtonDown(SDL_BUTTON_LEFT))
	{
		this->SetTexture(0);
	}
	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyTapped(SDL_SCANCODE_A))
	{
		this->_label->SetText(this->_label->GetText() + "A");
	}*/
}

void HMEngine::UI::TextBox::AttachToGameEngineEvent(HMEngine::GameEngine& gameEngine)
{
	gameEngine.AddUI(this->_label);
}

void HMEngine::UI::TextBox::KeyDownEvent(const unsigned int& keyCode)
{
	if (this->_isFocused && keyCode == SDL_SCANCODE_A)
		this->_label->SetText(this->_label->GetText() + "A");
}

void HMEngine::UI::TextBox::MouseButtonDownEvent(const unsigned int& mouseButtonCode)
{
	if (this->_isFocused = HMEngine::Core::Hardware::HardwareInputs::IsCursorWithinBoundaries(this->_quadDetails.topLeft, this->_quadDetails.bottomRight))
		this->SetTexture(1);
	else
		this->SetTexture(0);
}
