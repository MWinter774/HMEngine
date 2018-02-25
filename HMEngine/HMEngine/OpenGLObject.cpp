#include "OpenGLObject.h"
#include <variant>

HMEngine::OpenGL::OpenGLObject::OpenGLObject() : _isInitialized(false)
{

}

HMEngine::OpenGL::OpenGLObject::~OpenGLObject()
{
	if (this->_isInitialized)
		this->DeleteBuffers();
}

HMEngine::OpenGL::OpenGLObject::OpenGLObject(const HMEngine::OpenGL::OpenGLObject& other) : _vboCount(other._vboCount), _isInitialized(false),
_indices(other._indices), _normals(other._normals), _3dVertices(other._3dVertices), _uvs(other._uvs), _3dVerticesIndex(other._3dVerticesIndex),
_uvsIndex(other._uvsIndex), _normalsIndex(other._normalsIndex), _2dVertices(other._2dVertices), _2dVerticesIndex(other._2dVerticesIndex)
{
}

HMEngine::OpenGL::OpenGLObject& HMEngine::OpenGL::OpenGLObject::operator=(const HMEngine::OpenGL::OpenGLObject& other)
{
	if (this != &other)
	{
		if (this->_isInitialized)
			this->DeleteBuffers();
		this->_vboCount = other._vboCount;
		this->_isInitialized = false;
		this->_indices = other._indices;
		this->_3dVertices = other._3dVertices;
		this->_3dVerticesIndex = other._3dVerticesIndex;
		this->_2dVertices = other._2dVertices;
		this->_2dVerticesIndex = other._2dVerticesIndex;
		this->_normals = other._normals;
		this->_normalsIndex = other._normalsIndex;
		this->_uvs = other._uvs;
		this->_uvsIndex = other._uvsIndex;
	}

	return *this;
}

void HMEngine::OpenGL::OpenGLObject::Initialize()
{
	if (this->_isInitialized)
		this->DeleteBuffers();
	this->InitBuffers();
	this->InitVBO();
	this->_isInitialized = true;
}

/*
drawMode - mode of the drawing operation(GL_TRIANGLES, GL_TRIANGLE_STRIP...)
*/
void HMEngine::OpenGL::OpenGLObject::Draw(const unsigned char& drawMode)
{
	if (!this->_isInitialized) this->Initialize();
	glBindVertexArray(this->_vao);
	if (!this->_hasIndices)
	{
		int size = this->_3dVertices.size();
		if (size > 0)
			glDrawArrays(drawMode, 0, size);
		else
			glDrawArrays(drawMode, 0, this->_2dVertices.size());
	}
	else
	{
		glDrawElements(GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}

void HMEngine::OpenGL::OpenGLObject::InitVBO()
{
	glBindVertexArray(this->_vao);
	/* Generates the 3d vertices buffer */
	if (this->_3dVertices.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[this->_3dVerticesIndex]);
		glBufferData(GL_ARRAY_BUFFER, this->_3dVertices.size() * sizeof(this->_3dVertices[0]), &this->_3dVertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(this->_3dVerticesIndex);
		glVertexAttribPointer(this->_3dVerticesIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	/* Generates the 2d vertices buffer */
	else if (this->_2dVertices.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[this->_2dVerticesIndex]);
		glBufferData(GL_ARRAY_BUFFER, this->_2dVertices.size() * sizeof(this->_2dVertices[0]), &this->_2dVertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(this->_2dVerticesIndex);
		glVertexAttribPointer(this->_2dVerticesIndex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	/* Generates the uvs buffer */
	if (this->_uvs.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[this->_uvsIndex]);
		glBufferData(GL_ARRAY_BUFFER, (this->_uvs.size() * sizeof(this->_uvs[0])), &this->_uvs[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(this->_uvsIndex);
		glVertexAttribPointer(this->_uvsIndex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	/* Generates the normals buffer */
	if (this->_normals.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[this->_normalsIndex]);
		glBufferData(GL_ARRAY_BUFFER, (this->_normals.size() * sizeof(this->_normals[0])), &this->_normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(this->_normalsIndex);
		glVertexAttribPointer(this->_normalsIndex, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	}

	glBindVertexArray(0);
}

void HMEngine::OpenGL::OpenGLObject::InitBuffers()
{
	this->CalculateVBOCount();
	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);
	this->_vbo = std::vector<GLuint>(this->_vboCount);
	glGenBuffers(this->_vboCount, &this->_vbo[0]);
	glBindVertexArray(0);
}

void HMEngine::OpenGL::OpenGLObject::DeleteBuffers()
{
	glBindVertexArray(this->_vao);
	glDeleteBuffers(this->_vbo.size(), &this->_vbo[0]);
	glDeleteBuffers(1, &this->_vao);
	this->_isInitialized = false;
	this->_2dVertices.clear();
	this->_2dVerticesIndex = 0;
	this->_3dVertices.clear();
	this->_3dVerticesIndex = 0;
	this->_indices.clear();
	this->_normals.clear();
	this->_normalsIndex = 0;
	this->_uvs.clear();
	this->_uvsIndex = 0;
}

void HMEngine::OpenGL::OpenGLObject::CalculateVBOCount()
{
	if (this->_3dVertices.size() > 0)
	{
		this->_3dVerticesIndex = this->_vboCount;
		this->_vboCount++;
	}
	if (this->_2dVertices.size() > 0)
	{
		this->_2dVerticesIndex = this->_vboCount;
		this->_vboCount++;
	}
	if (this->_uvs.size() > 0)
	{
		this->_uvsIndex = this->_vboCount;
		this->_vboCount++;
	}
	if (this->_indices.size() > 0)
	{
		this->_vboCount++;
	}
	if (this->_normals.size() > 0)
	{
		this->_normalsIndex = this->_vboCount;
		this->_vboCount++;
	}
}