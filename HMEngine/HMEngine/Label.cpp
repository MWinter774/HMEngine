#include "Label.h"

HMEngine::UI::Label::Label(const std::string& name, const glm::vec2& position, const glm::vec2& scale, const std::string& text, 
	const HMEngine::UI::Font& font) : HMEngine::UI::Quad(name, font.GetFntTexturePath(), position, scale), _text(text), _font(font)
{
}

HMEngine::UI::Label::~Label()
{
}

void HMEngine::UI::Label::AttachToGameEngineEvent()
{
	/* Inits the vertices and uvs data of the quad */
}