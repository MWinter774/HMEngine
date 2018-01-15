#include "Texture.h"
#include "TextureManager.h"
#include "Utilities.h"

HMEngine::OpenGL::Texture::Texture(const std::string& texturePath)
{
	*this = HMEngine::OpenGL::TextureManager::GetTexture(texturePath);
}

HMEngine::OpenGL::Texture::~Texture()
{
	glDeleteTextures(1, &this->_textureId);
}

HMEngine::OpenGL::Texture::Texture(const HMEngine::OpenGL::Texture& other)
{
	this->_textureImage = other._textureImage;
	this->_textureId = other._textureId;
}

HMEngine::OpenGL::Texture& HMEngine::OpenGL::Texture::operator=(const HMEngine::OpenGL::Texture& other)
{
	if (this != &other)
	{
		this->_textureImage = other._textureImage;
		this->_textureId = other._textureId;
	}

	return *this;
}

void HMEngine::OpenGL::Texture::Bind() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->_textureId);
}

HMEngine::OpenGL::Texture::Texture(const std::string& texturePath, bool _1)
{
	/* Loads the image */
	int image = lodepng::decode(this->_textureImage.image, this->_textureImage.width, this->_textureImage.height, texturePath);
	if (image) //if the texture wasn't loaded successfully
	{
		HMEngine::Core::Utilities::ThrowException("ERROR WHILE LOADING TEXTURE: " + texturePath, "Texture Loading Error");
	}
	this->_textureImage.imagePath = texturePath;

	/* Generates and configures the texture buffer */
	glGenTextures(1, &this->_textureId); //generate one texture
	glBindTexture(GL_TEXTURE_2D, this->_textureId); //binds the texture so its properties can be changed
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_textureImage.width, this->_textureImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &this->_textureImage.image[0]); //fill the buffer with the texture
																																								//changes the properties of the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //sets how the texture will sample if an invalid coordinate is given
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //sets how the texture will sample if an invalid coordinate is given
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //sets the filtering function
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //sets the filtering function
	glGenerateMipmap(GL_TEXTURE_2D); //generate mipmap of the texture
}