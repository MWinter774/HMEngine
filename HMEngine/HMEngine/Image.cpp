#include "Image.h"
#include "UITexture.h"

HMEngine::UI::Image::Image(const std::string& name, const std::string& texturePath, const glm::vec2& position, const glm::vec2& scale) : HMEngine::UI::Quad(name, texturePath, HMEngine::UI::Quad::rectangle, position, scale)
{
}

HMEngine::UI::Image::~Image()
{
}