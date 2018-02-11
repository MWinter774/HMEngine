#include "Button.h"
#include "HardwareInputs.h"
#include <iostream>

HMEngine::UI::Button::Button(const std::string& name, const std::string& texturePath, const glm::vec2& position, const glm::vec2& scale) : HMEngine::UI::Quad(name, texturePath, HMEngine::UI::Quad::rectangle, position, scale)
{
}

HMEngine::UI::Button::~Button()
{
}

void HMEngine::UI::Button::Update()
{
	if (HMEngine::Core::Hardware::HardwareInputs::IsCursorWithinBoundaries(this->_topLeft, this->_bottomRight))
	{
		if (HMEngine::Core::Hardware::HardwareInputs::IsMouseButtonTapped(SDL_BUTTON_LEFT))
		{
			std::cout << "Click!" << std::endl;
		}
	}
}