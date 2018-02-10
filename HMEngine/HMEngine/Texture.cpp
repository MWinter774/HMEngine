#include "Texture.h"
#include "TextureManager.h"
#include "Utilities.h"

HMEngine::OpenGL::Texture::Texture(const std::string& texturePath)
{
	this->_texture = &HMEngine::OpenGL::TextureManager::GetTexture(texturePath);
}

HMEngine::OpenGL::Texture::~Texture()
{
}

HMEngine::OpenGL::Texture::Texture(const HMEngine::OpenGL::Texture& other)
{
	this->_texture = other._texture;
}

HMEngine::OpenGL::Texture& HMEngine::OpenGL::Texture::operator=(const HMEngine::OpenGL::Texture& other)
{
	if (this != &other)
	{
		delete this->_texture;
		this->_texture = other._texture;
	}

	return *this;
}

void HMEngine::OpenGL::Texture::Bind() const
{
	this->_texture->Bind();
}