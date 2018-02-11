#include "Image.h"
#include "UITexture.h"
#include <iostream>
#include "HardwareInputs.h"
#include "GameSettings.h"

HMEngine::UI::Image::Image(const std::string& name, const std::string& texturePath, const glm::vec2& position, const glm::vec2& scale) : HMEngine::UI::Quad(name, texturePath, HMEngine::UI::Quad::rectangle, position, scale)
{
}

HMEngine::UI::Image::~Image()
{
}

void HMEngine::UI::Image::Update()
{
	if (HMEngine::Core::Hardware::HardwareInputs::IsCursorWithinBoundaries(this->_topLeft, this->_bottomRight))
	{
		if (HMEngine::Core::Hardware::HardwareInputs::IsMouseButtonTapped(SDL_BUTTON_LEFT))
		{
			std::cout << "Click!" << std::endl;
		}
	}
}
