#include "ContextMenu.h"
#include "Button.h"
#include "Fonts.h"
#include "GameEngine.h"

const float HMEngine::UI::ContextMenu::BUTTON_HEIGHT = 20.0f;

HMEngine::UI::ContextMenu::ContextMenu(const std::string& name, const glm::vec2& position) :
	HMEngine::UI::Quad(name, position, glm::vec2(120, 0)), _buttons()
{
	this->InitializeEvents<ContextMenu>(this);
}

HMEngine::UI::ContextMenu::~ContextMenu()
{
}

HMEngine::UI::ContextMenu::ContextMenu(const HMEngine::UI::ContextMenu& other) : HMEngine::UI::Quad(other)
{
	this->InitializeEvents<ContextMenu>(this);
	for (auto& button : other._buttons)
	{
		this->_buttons.push_back(new HMEngine::UI::Button(*button));
	}
}

HMEngine::UI::ContextMenu& HMEngine::UI::ContextMenu::operator=(const HMEngine::UI::ContextMenu& other)
{
	if (this != &other)
	{
		HMEngine::UI::Quad::operator=(other);
		this->InitializeEvents<ContextMenu>(this);
		for (auto& button : other._buttons)
		{
			this->_buttons.push_back(new HMEngine::UI::Button(*button));
		}
	}

	return *this;
}

void HMEngine::UI::ContextMenu::AddButton(const std::string& buttonName, const std::string& buttonText, const std::function<void(HMEngine::UI::Button*)>& onClickEvent)
{
	HMEngine::UI::Button* newButton = new HMEngine::UI::Button(buttonName, "./resources/UITextures/ContextMenuButtonReleased.png",
		"./resources/UITextures/ContextMenuButtonHovered.png", "./resources/UITextures/ContextMenuButtonHovered.png",
		glm::vec2(this->_quadDetails.position.x, this->_quadDetails.position.y + HMEngine::UI::ContextMenu::BUTTON_HEIGHT * this->_buttons.size()),
		glm::vec2(this->_quadDetails.width, HMEngine::UI::ContextMenu::BUTTON_HEIGHT), buttonText, HMEngine::Fonts::ARIAL, glm::vec3(0), 0.1f);

	this->SetScale(this->_quadDetails.width, this->_quadDetails.height + HMEngine::UI::ContextMenu::BUTTON_HEIGHT * 2.0f);

	newButton->SetVisiblity(this->_isVisible);

	*newButton += onClickEvent;

	this->_buttons.push_back(newButton);
	this->AddChild(newButton);
}

void HMEngine::UI::ContextMenu::AddButton(const std::string& buttonName, const std::string& buttonText)
{
	HMEngine::UI::Button* newButton = new HMEngine::UI::Button(buttonName, "./resources/UITextures/ContextMenuButtonReleased.png",
		"./resources/UITextures/ContextMenuButtonHovered.png", "./resources/UITextures/ContextMenuButtonHovered.png",
		glm::vec2(this->_quadDetails.position.x, this->_quadDetails.position.y + HMEngine::UI::ContextMenu::BUTTON_HEIGHT * this->_buttons.size()),
		glm::vec2(this->_quadDetails.width, HMEngine::UI::ContextMenu::BUTTON_HEIGHT), buttonText, HMEngine::Fonts::ARIAL, glm::vec3(0), 0.1f);

	this->SetScale(this->_quadDetails.width, this->_quadDetails.height + HMEngine::UI::ContextMenu::BUTTON_HEIGHT * 2.0f);

	newButton->SetVisiblity(this->_isVisible);

	this->_buttons.push_back(newButton);
	this->AddChild(newButton);
}