#include "OpenGLObject.h"

HMEngine::OpenGL::OpenGLObject::OpenGLObject(const std::vector<std::any>& vboData) : _vboCount(vboData.size()), _vboCounter(0), _vboData(vboData)
{
	this->InitBuffers();
	this->InitVBOFromVector(this->_vboData);
}

HMEngine::OpenGL::OpenGLObject::~OpenGLObject()
{
	this->DeleteBuffers();
}

HMEngine::OpenGL::OpenGLObject::OpenGLObject(const HMEngine::OpenGL::OpenGLObject& other) : _vboData(other._vboData), _vboCount(other._vboCount), _vboCounter(0)
{
	this->InitBuffers();
	this->InitVBOFromVector(this->_vboData);
}

HMEngine::OpenGL::OpenGLObject& HMEngine::OpenGL::OpenGLObject::operator=(const HMEngine::OpenGL::OpenGLObject& other)
{
	if (this != &other)
	{
		this->DeleteBuffers();
		this->_vboData = other._vboData;
		this->_vboCount = other._vboCount;
		this->_vboCounter = 0;
		this->InitBuffers();
		this->InitVBOFromVector(this->_vboData);
	}

	return *this;
}

void HMEngine::OpenGL::OpenGLObject::InitVBOFromVector(const std::vector<std::any>& vboData)
{
}

void HMEngine::OpenGL::OpenGLObject::InitBuffers()
{
	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);
	this->_vbo = std::vector<GLuint>(this->_vboCount);
	glGenBuffers(this->_vboCount, &this->_vbo[0]);
}

void HMEngine::OpenGL::OpenGLObject::DeleteBuffers()
{
	glBindVertexArray(this->_vao);
	glDisableVertexAttribArray(0);
	glDeleteBuffers(this->_vbo.size(), &this->_vbo[0]);
	glDeleteBuffers(1, &this->_vao);
}
