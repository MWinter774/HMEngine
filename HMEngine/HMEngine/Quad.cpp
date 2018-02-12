#include "Quad.h"
#include "UITexture.h"
#include "Transform.h"
#include <math.h>
#include <iostream>
#include "Utilities.h"
#include "GameSettings.h"
#include "OpenGLQuad.h"

const std::vector<glm::vec2> HMEngine::UI::Quad::rectangle = { glm::vec2(-1,1),glm::vec2(-1,-1), glm::vec2(1,1),glm::vec2(1,-1) };

HMEngine::UI::Quad::Quad(const std::string& name, const std::string& texturePath, const std::vector<glm::vec2>& vertices, const glm::vec2& position, const glm::vec2& scale) :
	_name(name), _vertices(vertices), _gameEngine(nullptr), _textures{ new HMEngine::OpenGL::UITexture(texturePath) },
	_isAddedToGameEngine(false), _quad(nullptr), _transform(new HMEngine::Core::Transform())
{
	this->_currentTexture = _textures[0];

	this->_quadDetails.position = position;
	this->_quadDetails.scale = scale;
	this->UpdateQuadDetails();

	this->UpdateTransform();
}

HMEngine::UI::Quad::Quad(const std::string& name, const std::string& texturePath, const glm::vec2& position, const glm::vec2& scale) :
	Quad(name, texturePath, HMEngine::UI::Quad::rectangle, position, scale)
{
}

HMEngine::UI::Quad::~Quad()
{
	if (this->_isAddedToGameEngine)
	{
		delete this->_quad;
	}
	for (auto& texture : this->_textures)
	{
		delete texture;
	}
	delete this->_transform;
}

HMEngine::UI::Quad::Quad(const HMEngine::UI::Quad& other) : _name(other._name), _vertices(other._vertices), _quadDetails(other._quadDetails),
_gameEngine(other._gameEngine), _isAddedToGameEngine(other._isAddedToGameEngine), _transform(new HMEngine::Core::Transform(*other._transform))
{
	for (auto& otherTexture : other._textures)
	{
		this->_textures.push_back(new HMEngine::OpenGL::UITexture(*otherTexture));
	}
	this->_currentTexture = this->_textures[0];
	if (this->_isAddedToGameEngine)
		this->_quad = new HMEngine::OpenGL::OpenGLQuad(*other._quad);
}

HMEngine::UI::Quad& HMEngine::UI::Quad::operator=(const HMEngine::UI::Quad& other)
{
	if (this != &other)
	{
		for (auto& texture : this->_textures)
		{
			delete texture;
		}
		for (auto& otherTexture : other._textures)
		{
			this->_textures.push_back(new HMEngine::OpenGL::UITexture(*otherTexture));
		}
		this->_currentTexture = this->_textures[0];
		delete this->_transform;
		this->_transform = new HMEngine::Core::Transform(*other._transform);

		this->_vertices = other._vertices;
		this->_name = other._name;
		this->_quadDetails = other._quadDetails;
		this->_isAddedToGameEngine = other._isAddedToGameEngine;
		if (this->_isAddedToGameEngine)
		{
			if (this->_quad != nullptr)
			{
				delete this->_quad;
			}
			this->_quad = new HMEngine::OpenGL::OpenGLQuad(*other._quad);
		}
	}

	return *this;
}

void HMEngine::UI::Quad::AddTexture(const std::string& texturePath)
{
	this->_textures.push_back(new HMEngine::OpenGL::UITexture(texturePath));
}

void HMEngine::UI::Quad::SetTexture(unsigned int i)
{
	if (i >= this->_textures.size())
	{
		HMEngine::Core::Utilities::ThrowException("Quad texture index is out of range!");
	}
	this->_currentTexture = this->_textures[i];
}

void HMEngine::UI::Quad::BindTexture() const
{
	this->_currentTexture->Bind();
}

void HMEngine::UI::Quad::Draw() const
{
	this->_quad->Draw();
}

void HMEngine::UI::Quad::AttachToGameEngine()
{
	this->_isAddedToGameEngine = true;
	this->_quad = new HMEngine::OpenGL::OpenGLQuad(this->_vertices);

	this->AttachToGameEngineEvent();
}

void HMEngine::UI::Quad::UpdateTransform()
{
	glm::vec2 position(this->_quadDetails.position.x, HMEngine::GameSettings::GetWindowHeight() - this->_quadDetails.position.y);

	float fixedPositionX = (2 * position.x - HMEngine::GameSettings::GetWindowWidth()) / HMEngine::GameSettings::GetWindowWidth();
	float fixedPositionY = (2 * position.y - HMEngine::GameSettings::GetWindowHeight()) / HMEngine::GameSettings::GetWindowHeight();
	glm::vec2 fixedPosition = glm::vec2(fixedPositionX, fixedPositionY);
	float fixedScaleX = this->_quadDetails.scale.x / HMEngine::GameSettings::GetWindowWidth();
	float fixedScaleY = this->_quadDetails.scale.y / HMEngine::GameSettings::GetWindowHeight();
	glm::vec2 fixedScale(fixedScaleX, fixedScaleY);

	this->_transform->SetPosition(glm::vec3(fixedPosition, 0.0f));
	this->_transform->SetScale(glm::vec3(fixedScale, 1.0f));
}

void HMEngine::UI::Quad::UpdateQuadDetails()
{
	float width = this->_quadDetails.scale.x;
	float height = this->_quadDetails.scale.y;
	this->_quadDetails.width = width;
	this->_quadDetails.height = height;
	this->_quadDetails.topLeft = glm::vec2(this->_quadDetails.position.x - width / 2, this->_quadDetails.position.y - height / 2);
	this->_quadDetails.bottomRight = glm::vec2(this->_quadDetails.position.x + width / 2, this->_quadDetails.position.y + height / 2);
}