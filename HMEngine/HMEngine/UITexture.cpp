#include "UITexture.h"
#include "Texture.h"

HMEngine::OpenGL::UITexture::UITexture(const std::string& texturePath) : _texture(new HMEngine::OpenGL::Texture(texturePath))
{
}

HMEngine::OpenGL::UITexture::~UITexture()
{
	delete this->_texture;
}

HMEngine::OpenGL::UITexture::UITexture(const HMEngine::OpenGL::UITexture& other) : _texture(new HMEngine::OpenGL::Texture(*other._texture))
{
}

HMEngine::OpenGL::UITexture& HMEngine::OpenGL::UITexture::operator=(const HMEngine::OpenGL::UITexture& other)
{
	if (this != &other)
	{
		delete this->_texture;
		this->_texture = new HMEngine::OpenGL::Texture(*other._texture);
	}

	return *this;
}

void HMEngine::OpenGL::UITexture::Bind() const
{
	this->_texture->Bind();
}