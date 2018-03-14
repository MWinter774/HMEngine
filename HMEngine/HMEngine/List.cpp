#include "List.h"
#include "Image.h"
#include "Button.h"
#include "Fonts.h"

HMEngine::UI::List::List(const std::string& name, const glm::vec2& position, const glm::vec2& scale, const std::string& backgroundTextureFilePath) :
	HMEngine::UI::Quad(name, position, scale), _background(new HMEngine::UI::Image(name + "_background", backgroundTextureFilePath, position, scale))
{
	this->AddChild(this->_background);
	this->InitializeEvents<List>(this);
}

HMEngine::UI::List::~List()
{
}

HMEngine::UI::List::List(const HMEngine::UI::List& other) : HMEngine::UI::Quad(other)
{
	this->InitializeEvents<List>(this);
}

HMEngine::UI::List& HMEngine::UI::List::operator=(const HMEngine::UI::List& other)
{
	if (this != &other)
	{
		this->InitializeEvents<List>(this);
		HMEngine::UI::Quad::operator=(other);
	}

	return *this;
}

HMEngine::UI::Button* HMEngine::UI::List::AddButton(const std::string& text, std::function<void(HMEngine::UI::Button*)> onClickEvent)
{
	float btnWidth = this->_quadDetails.width;
	float btnHeight = 25.0f;
	HMEngine::UI::Button* btn = new HMEngine::UI::Button(this->_name + "_btn" + std::to_string(this->_buttons.size()), "./resources/UITextures/listButtonReleased.png",
		"./resources/UITextures/listButtonPressed.png", "./resources/UITextures/listButtonPressed.png",
		glm::vec2(this->_quadDetails.topLeft.x + btnWidth / 2, this->_quadDetails.topLeft.y + btnHeight / 2 + btnHeight * this->_buttons.size()),
		glm::vec2(btnWidth, btnHeight), text, HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f);

	*btn += onClickEvent;

	this->_buttons.push_back(btn);
	this->AddChild(btn);

	return btn;
}