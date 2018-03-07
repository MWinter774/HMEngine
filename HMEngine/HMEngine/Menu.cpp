#include "Menu.h"
#include "Button.h"
#include "GameEngine.h"

HMEngine::UI::Menu::Menu(const std::string& name, const glm::vec2& position, const glm::vec2& scale, const std::string& backgroundTexturePath) :
	HMEngine::UI::Quad(name, backgroundTexturePath, position, scale)
{
	this->InitializeEvents<Menu>(this);
}

HMEngine::UI::Menu::~Menu()
{
}

HMEngine::UI::Menu::Menu(const HMEngine::UI::Menu& other) : HMEngine::UI::Quad(other)
{
	this->InitializeEvents<Menu>(this);
}

HMEngine::UI::Menu& HMEngine::UI::Menu::operator=(const HMEngine::UI::Menu& other)
{
	if (this != &other)
	{
		HMEngine::UI::Quad::operator=(other);
		this->InitializeEvents<Menu>(this);
	}

	return *this;
}

void HMEngine::UI::Menu::AddButton(const std::string& name, const std::string& buttonReleasedTexture, const std::string& buttonHoverTexture,
	const std::string& buttonPressedTexture, const glm::vec2& position, const glm::vec2& scale, const std::string& labelText,
	const HMEngine::UI::Font& font, const glm::vec3& labelTextColor, float labelFontSize)
{
	glm::vec2 newPos = this->_quadDetails.position + position;
	HMEngine::UI::Button* newButton = new HMEngine::UI::Button(name + "_" + this->_name, buttonReleasedTexture, buttonHoverTexture, buttonPressedTexture, newPos,
		scale, labelText, font, labelTextColor, labelFontSize);

	this->_buttons.push_back(newButton);
	this->AddChild(newButton);
}