#include "Quad.h"
#include "UITexture.h"
#include "Transform.h"
#include <math.h>
#include <iostream>
#include "Utilities.h"
#include "GameSettings.h"
#include "RenderingEngine.h"

const std::vector<glm::vec2> HMEngine::UI::Quad::rectangle = { glm::vec2(-1,1), glm::vec2(-1,-1), glm::vec2(1,1), glm::vec2(1,-1) };

HMEngine::UI::Quad::Quad(const std::string& name, const std::string& texturePath, const std::vector<glm::vec2>& vertices, const glm::vec2& position,
	const glm::vec2& scale) : _name(name), _gameEngine(nullptr), _isAddedToGameEngine(false), _transform(new HMEngine::Core::Transform()),
	_quadTextures{ new HMEngine::OpenGL::UITexture(texturePath) }, _openglQuad(new HMEngine::OpenGL::OpenGLQuad())
{
	this->_currentTexture = _quadTextures[0];
	this->_openglQuad->SetVertices(HMEngine::UI::Quad::rectangle);

	this->_quadDetails.position = position;
	this->_quadDetails.scale = scale;
	this->UpdateQuadDetails();

	this->UpdateTransform();
}

HMEngine::UI::Quad::Quad(const std::string& name, const std::string& texturePath, const glm::vec2& position, const glm::vec2& scale, bool useVertices) :
	_name(name), _gameEngine(nullptr), _isAddedToGameEngine(false), _transform(new HMEngine::Core::Transform()), _openglQuad(new HMEngine::OpenGL::OpenGLQuad()),
	_quadTextures{ new HMEngine::OpenGL::UITexture(texturePath) }
{
	this->_currentTexture = _quadTextures[0];
	if (useVertices)
		this->_openglQuad->SetVertices(HMEngine::UI::Quad::rectangle);

	this->_quadDetails.position = position;
	this->_quadDetails.scale = scale;
	this->UpdateQuadDetails();

	this->UpdateTransform();
}

HMEngine::UI::Quad::Quad(const std::string& name, const glm::vec2& position, const glm::vec2& scale) : _name(name), _gameEngine(nullptr),
_isAddedToGameEngine(false), _transform(new HMEngine::Core::Transform())
{
	this->_quadDetails.position = position;
	this->_quadDetails.scale = scale;
	this->UpdateQuadDetails();

	this->UpdateTransform();
}

HMEngine::UI::Quad::~Quad()
{
	for (auto& quadTexture : this->_quadTextures)
	{
		delete quadTexture;
	}

	delete this->_openglQuad;
	delete this->_transform;
}

HMEngine::UI::Quad::Quad(const HMEngine::UI::Quad& other) : _name(other._name), _quadDetails(other._quadDetails), _gameEngine(other._gameEngine),
_isAddedToGameEngine(other._isAddedToGameEngine), _transform(new HMEngine::Core::Transform(*other._transform))
{
	for (auto& quadTexture : other._quadTextures)
	{
		this->_quadTextures.push_back(new HMEngine::OpenGL::UITexture(*quadTexture));
	}
	if (this->_quadTextures.size() > 0)
		this->_currentTexture = this->_quadTextures[0];

	if (other._openglQuad != nullptr)
		this->_openglQuad = new HMEngine::OpenGL::OpenGLQuad(*other._openglQuad);
}

HMEngine::UI::Quad& HMEngine::UI::Quad::operator=(const HMEngine::UI::Quad& other)
{
	if (this != &other)
	{
		delete this->_transform;
		for (auto& quadTexture : this->_quadTextures)
		{
			delete quadTexture;
		}
		delete this->_openglQuad;

		this->_openglQuad = new HMEngine::OpenGL::OpenGLQuad(*other._openglQuad);
		this->_transform = new HMEngine::Core::Transform(*other._transform);
		this->_name = other._name;
		this->_quadDetails = other._quadDetails;
		this->_isAddedToGameEngine = other._isAddedToGameEngine;
		if (this->_isAddedToGameEngine)
		{
			for (auto& quadTexture : other._quadTextures)
			{
				this->_quadTextures.push_back(new HMEngine::OpenGL::UITexture(*quadTexture));
			}
			if (this->_quadTextures.size() > 0)
				this->_currentTexture = this->_quadTextures[0];
		}
	}

	return *this;
}

void HMEngine::UI::Quad::AddTexture(const std::string& texturePath)
{
	this->_quadTextures.push_back(new HMEngine::OpenGL::UITexture(texturePath));
}

void HMEngine::UI::Quad::SetTexture(unsigned int i)
{
	if (i >= this->_quadTextures.size())
	{
		HMEngine::Core::Utilities::ThrowException("Quad texture index is out of range!");
	}
	this->_currentTexture = this->_quadTextures[i];
}

void HMEngine::UI::Quad::BindTexture() const
{
	if (this->_currentTexture == nullptr)
		HMEngine::Core::Utilities::ThrowException("NO TEXTURE ASSIGNED TO QUAD!");
	this->_currentTexture->Bind();
}

void HMEngine::UI::Quad::Draw() const
{
	this->BindTexture();
	this->_openglQuad->Draw(GL_TRIANGLE_STRIP);
}

void HMEngine::UI::Quad::AttachToGameEngine(HMEngine::GameEngine& gameEngine)
{
	this->_isAddedToGameEngine = true;
	if (this->_openglQuad != nullptr)
		this->_openglQuad->Initialize();

	this->AttachToGameEngineEvent(gameEngine);
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