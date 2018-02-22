#include "OpenGLQuad.h"

HMEngine::OpenGL::OpenGLQuad::OpenGLQuad()
{
}

HMEngine::OpenGL::OpenGLQuad::OpenGLQuad(const std::vector<glm::vec2>& vertices)
{
	this->SetVertices(vertices);
}

HMEngine::OpenGL::OpenGLQuad::OpenGLQuad(const std::vector<glm::vec2>& vertices, const std::vector<glm::vec2>& uvs)
{
	this->SetVertices(vertices);
	this->SetUVs(uvs);
}

HMEngine::OpenGL::OpenGLQuad::~OpenGLQuad()
{
}