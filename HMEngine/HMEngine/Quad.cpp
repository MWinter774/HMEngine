#include "Quad.h"
#include "UITexture.h"
#include "Transform.h"
#include "GameSettings.h"
#include <math.h>
#include <iostream>

const std::vector<glm::vec2> HMEngine::UI::Quad::rectangle = { glm::vec2(-1,1),glm::vec2(-1,-1), glm::vec2(1,1),glm::vec2(1,-1) };

HMEngine::UI::Quad::Quad(const std::string& name, const std::string& texturePath, const std::vector<glm::vec2>& vertices, const glm::vec2& position, const glm::vec2& scale) : _name(name), _vertices(vertices), _scale(scale), _gameEngine(nullptr), _texture(new HMEngine::OpenGL::UITexture(texturePath)), _isAddedToGameEngine(false), _position(position)
{
	float fixedPositionX = (2 * position.x - HMEngine::GameSettings::GetWindowWidth()) / HMEngine::GameSettings::GetWindowWidth();
	float fixedPositionY = (2 * position.y - HMEngine::GameSettings::GetWindowHeight()) / HMEngine::GameSettings::GetWindowHeight();
	this->_transform = new HMEngine::Core::Transform(glm::vec3(glm::vec2(fixedPositionX, fixedPositionY), 0.0f), glm::vec3(0), glm::vec3(scale, 1.0f));
}

HMEngine::UI::Quad::~Quad()
{
	if (this->_isAddedToGameEngine)
	{
		glBindVertexArray(this->_vao);
		glDisableVertexAttribArray(0);
		glDeleteBuffers(this->VBO_COUNT, this->_vbo);
		glDeleteBuffers(1, &this->_vao);
		glBindVertexArray(0);
	}
	delete this->_texture;
	delete this->_transform;
}

HMEngine::UI::Quad::Quad(const HMEngine::UI::Quad& other) : _name(other._name), _vertices(other._vertices), _scale(other._scale), _gameEngine(other._gameEngine), _texture(new HMEngine::OpenGL::UITexture(*other._texture)), _isAddedToGameEngine(other._isAddedToGameEngine), _position(other._position), _transform(new HMEngine::Core::Transform(*other._transform))
{
	if (this->_isAddedToGameEngine)
		this->InitBuffers();
}

HMEngine::UI::Quad& HMEngine::UI::Quad::operator=(const HMEngine::UI::Quad& other)
{
	if (this != &other)
	{
		delete this->_texture;
		this->_texture = new HMEngine::OpenGL::UITexture(*other._texture);
		delete this->_transform;
		this->_transform = new HMEngine::Core::Transform(*other._transform);

		this->_vertices = other._vertices;
		this->_name = other._name;
		this->_scale = other._scale;
		this->_position = other._position;
		this->_isAddedToGameEngine = other._isAddedToGameEngine;
		if (this->_isAddedToGameEngine)
		{
			glBindVertexArray(this->_vao);
			glDisableVertexAttribArray(0);
			glDeleteBuffers(this->VBO_COUNT, this->_vbo);
			glDeleteBuffers(1, &this->_vao);
			glBindVertexArray(0);

			this->InitBuffers();
		}
	}

	return *this;
}

void HMEngine::UI::Quad::BindTexture() const
{
	this->_texture->Bind();
}

void HMEngine::UI::Quad::Draw() const
{
	glBindVertexArray(this->_vao);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->_vertices.size());
}

void HMEngine::UI::Quad::AttachToGameEngine()
{
	this->_isAddedToGameEngine = true;
	this->InitBuffers();

	this->AttachToGameEngineEvent();
}

void HMEngine::UI::Quad::InitBuffers()
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
