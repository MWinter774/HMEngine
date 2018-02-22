#include "TerrainTexture.h"
#include "Texture.h"
#include <GL\glew.h>

HMEngine::OpenGL::TerrainTexture::TerrainTexture(const std::string& backroundTextureFilePath, const std::string& rTextureFilePath, 
	const std::string& gTextureFilePath, const std::string& bTextureFilePath, const std::string& blendMapFilePath) : 
	_backgroundTexture(new HMEngine::OpenGL::Texture(backroundTextureFilePath, GL_RGB)), _rTexture(new HMEngine::OpenGL::Texture(rTextureFilePath, GL_RGB)),
	_gTexture(new HMEngine::OpenGL::Texture(gTextureFilePath, GL_RGB)), _bTexture(new HMEngine::OpenGL::Texture(bTextureFilePath, GL_RGB)),
	_blendMap(new HMEngine::OpenGL::Texture(blendMapFilePath, GL_RGB))
{
}

HMEngine::OpenGL::TerrainTexture::~TerrainTexture()
{
	delete this->_backgroundTexture;
	delete this->_rTexture;
	delete this->_gTexture;
	delete this->_bTexture;
	delete this->_blendMap;
}

HMEngine::OpenGL::TerrainTexture::TerrainTexture(const HMEngine::OpenGL::TerrainTexture& other)
{
	this->_backgroundTexture = new HMEngine::OpenGL::Texture(*other._backgroundTexture);
	this->_rTexture = new HMEngine::OpenGL::Texture(*other._rTexture);
	this->_gTexture = new HMEngine::OpenGL::Texture(*other._gTexture);
	this->_bTexture = new HMEngine::OpenGL::Texture(*other._bTexture);
	this->_blendMap = new HMEngine::OpenGL::Texture(*other._blendMap);
}

HMEngine::OpenGL::TerrainTexture& HMEngine::OpenGL::TerrainTexture::operator=(const HMEngine::OpenGL::TerrainTexture& other)
{
	if (this != &other)
	{
		delete this->_backgroundTexture;
		delete this->_rTexture;
		delete this->_gTexture;
		delete this->_bTexture;
		delete this->_blendMap;

		this->_backgroundTexture = new HMEngine::OpenGL::Texture(*other._backgroundTexture);
		this->_rTexture = new HMEngine::OpenGL::Texture(*other._rTexture);
		this->_gTexture = new HMEngine::OpenGL::Texture(*other._gTexture);
		this->_bTexture = new HMEngine::OpenGL::Texture(*other._bTexture);
		this->_blendMap = new HMEngine::OpenGL::Texture(*other._blendMap);
	}

	return *this;
}

void HMEngine::OpenGL::TerrainTexture::Bind() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->_backgroundTexture->GetTextureId());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->_rTexture->GetTextureId());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, this->_gTexture->GetTextureId());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, this->_bTexture->GetTextureId());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, this->_blendMap->GetTextureId());
}