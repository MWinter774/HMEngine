#include "Label.h"

HMEngine::UI::Label::Label(const std::string& name, const std::string& texturePath, const glm::vec2& position, const glm::vec2& scale, const std::string& text, 
	const HMEngine::UI::Font& font) : HMEngine::UI::Quad(name, texturePath, HMEngine::UI::Quad::rectangle, position, scale),
_text(text), _font(font)
{
}

HMEngine::UI::Label::~Label()
{
}