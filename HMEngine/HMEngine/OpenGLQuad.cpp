#include "OpenGLQuad.h"

HMEngine::OpenGL::OpenGLQuad::OpenGLQuad(const std::vector<glm::vec2>& vertices) : _vertices(vertices)
{
	this->InitBuffers();
}

HMEngine::OpenGL::OpenGLQuad::~OpenGLQuad()
{
	glBindVertexArray(this->_vao);
	glDisableVertexAttribArray(0);
	glDeleteBuffers(this->VBO_COUNT, this->_vbo);
	glDeleteBuffers(1, &this->_vao);
	glBindVertexArray(0);
}

HMEngine::OpenGL::OpenGLQuad::OpenGLQuad(const HMEngine::OpenGL::OpenGLQuad& other) : _vertices(other._vertices)
{
	this->InitBuffers();
}

HMEngine::OpenGL::OpenGLQuad& HMEngine::OpenGL::OpenGLQuad::operator=(const HMEngine::OpenGL::OpenGLQuad& other)
{
	if (this != &other)
	{
		this->_vertices = other._vertices;
		this->InitBuffers();
	}

	return *this;
}

void HMEngine::OpenGL::OpenGLQuad::Draw() const
{
	glBindVertexArray(this->_vao);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->_vertices.size());
}

void HMEngine::OpenGL::OpenGLQuad::InitBuffers()
{
	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);

	glGenBuffers(this->VBO_COUNT, this->_vbo);

	/* Generates the vertices buffer */
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[this->VBO_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(this->_vertices[0]), &this->_vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);
}
