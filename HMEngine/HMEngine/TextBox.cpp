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

void HMEngine::UI::TextBox::AttachToGameEngineEvent()
{
	this->_gameEngine->AddUI(this->_label);
}

void HMEngine::UI::TextBox::KeyDownEvent(const unsigned int& keyCode)
{
	bool needToUpdateString = true;
	std::string newText = this->_label->GetText();
	if (this->_isFocused)
	{
		if (keyCode >= SDL_SCANCODE_A && keyCode <= SDL_SCANCODE_Z)
		{
			newText += keyCode + ('a' - SDL_SCANCODE_A);
		}
		else if (keyCode == SDL_SCANCODE_SPACE) //keyCode is a space
		{
			newText += ' ';
		}
		else if (keyCode >= SDL_SCANCODE_1 && keyCode < SDL_SCANCODE_0) //keyCode is a number
		{
			newText += keyCode + ('1' - SDL_SCANCODE_1);
		}
		else if (keyCode == SDL_SCANCODE_0) //keyCode is the number 0(number 0 code is the last one on the sdl scancode list)
		{
			newText += '0';
		}
		else if (keyCode == SDL_SCANCODE_BACKSPACE && !newText.empty()) //if user pressed backspace and the label is not empty
		{
			newText.pop_back();
		}
		else
		{
			needToUpdateString = false;
		}
		if (needToUpdateString)
		{
			this->_label->SetText(newText);
			this->_label->SetTopLeft(this->_quadDetails.topLeft);
		}
	}
}

void HMEngine::UI::TextBox::MouseButtonDownEvent(const unsigned int& mouseButtonCode)
{
	if (this->_isFocused = HMEngine::Core::Hardware::HardwareInputs::IsCursorWithinBoundaries(this->_quadDetails.topLeft, this->_quadDetails.bottomRight))
		this->SetTexture(1);
	else
		this->SetTexture(0);
}
