#include "TextBox.h"
#include "Label.h"
#include "GameEngine.h"
#include "HardwareInputs.h"

HMEngine::UI::TextBox::TextBox(const std::string& name, const glm::vec2& position, const glm::vec2& scale, const HMEngine::UI::Font& font, bool acceptLetters) :
	HMEngine::UI::Quad(name, "./resources/UITextures/TextBoxUnfocused.png", position, scale),
	_label(new HMEngine::UI::Label(name + "_textbox_label", position, scale, "", font, { 0,0,0 })), _isFocused(false), _acceptLetters(acceptLetters)
{
	this->InitializeEvents<TextBox>(this);
	this->AddTexture("./resources/UITextures/TextBoxFocused.png");
	this->AddChild(this->_label);
	this->_label->SetTopLeft(glm::vec2(this->_quadDetails.topLeft) += glm::vec2(0, -scale.x / 20.0f)); //basic ratio, needs fixing
}

HMEngine::UI::TextBox::~TextBox()
{
}

HMEngine::UI::TextBox::TextBox(const HMEngine::UI::TextBox& other) : HMEngine::UI::Quad(other), _label(new HMEngine::UI::Label(*other._label)), _isFocused(false),
_acceptLetters(other._acceptLetters)
{
	this->InitializeEvents<TextBox>(this);
	this->_label->SetTopLeft(glm::vec2(this->_quadDetails.topLeft) += glm::vec2(0, -4.5f));
}

HMEngine::UI::TextBox& HMEngine::UI::TextBox::operator=(const HMEngine::UI::TextBox& other)
{
	if (this != &other)
	{
		HMEngine::UI::Quad::operator=(other);
		this->_label = new HMEngine::UI::Label(*other._label);
		this->InitializeEvents<TextBox>(this);
		this->_isFocused = false;
		this->_acceptLetters = other._acceptLetters;
		this->_label->SetTopLeft(glm::vec2(this->_quadDetails.topLeft) += glm::vec2(0, -4.5f));
	}

	return *this;
}

void HMEngine::UI::TextBox::KeyDownEvent(const unsigned int& keyCode)
{
	bool needToUpdateString = true;
	std::string newText = this->_label->GetText();
	bool isShift = HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_LSHIFT) || HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_RSHIFT);

	if (this->_isFocused)
	{
		if (this->_acceptLetters && keyCode >= SDL_SCANCODE_A && keyCode <= SDL_SCANCODE_Z)
		{
			if (!isShift)
				newText += keyCode + ('a' - SDL_SCANCODE_A);
			else
				newText += keyCode + ('A' - SDL_SCANCODE_A);
		}
		else if (this->_acceptLetters && keyCode == SDL_SCANCODE_SPACE) //keyCode is a space
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
		else if (keyCode == SDL_SCANCODE_PERIOD || keyCode == SDL_SCANCODE_KP_PERIOD)
		{
			newText += '.';
		}
		else if (keyCode >= SDL_SCANCODE_KP_1 && keyCode < SDL_SCANCODE_KP_0)
		{
			newText += keyCode + ('1' - SDL_SCANCODE_KP_1);
		}
		else if (keyCode == SDL_SCANCODE_KP_0)
		{
			newText += '0';
		}
		else
		{
			needToUpdateString = false;
		}
		if (needToUpdateString)
		{
			this->_label->SetText(newText);
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

void HMEngine::UI::TextBox::SetText(const std::string& text)
{
	this->_label->SetText(text);
}
//
//int i = 0;
//void HMEngine::UI::TextBox::UpdateEvent()
//{
//	this->SetScale(cos(i / 200.0f) * 100.0f, this->_quadDetails.scale.y);
//	this->_label->SetTopLeft(glm::vec2(this->_quadDetails.topLeft));
//	i++;
//}
