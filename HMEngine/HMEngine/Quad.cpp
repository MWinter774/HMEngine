#include "Quad.h"
#include "UITexture.h"
#include "Transform.h"
#include <math.h>
#include <iostream>
#include "Utilities.h"
#include "GameSettings.h"
#include "RenderingEngine.h"
#include "GameEngine.h"

const std::vector<glm::vec2> HMEngine::UI::Quad::rectangle = { glm::vec2(-1,1), glm::vec2(-1,-1), glm::vec2(1,1), glm::vec2(1,-1) };

HMEngine::UI::Quad::Quad(const std::string& name, const std::string& texturePath, const std::vector<glm::vec2>& vertices, const glm::vec2& position,
	const glm::vec2& scale) : HMEngine::Core::EventObject(), _name(name), _transform(new HMEngine::Core::Transform()),
	_quadTextures{ new HMEngine::OpenGL::UITexture(texturePath) }, _openglQuad(new HMEngine::OpenGL::OpenGLQuad()), _isAttachedToGameEngine(false), _isVisible(true)
{
	this->_currentTexture = _quadTextures[0];
	this->_openglQuad->SetVertices(HMEngine::UI::Quad::rectangle);

	this->_quadDetails.position = position;
	this->_quadDetails.scale = scale;
	this->UpdateQuadDetails();

	this->UpdateTransform();
}

HMEngine::UI::Quad::Quad(const std::string& name, const std::string& texturePath, const glm::vec2& position, const glm::vec2& scale, bool useVertices) :
	HMEngine::Core::EventObject(), _name(name), _transform(new HMEngine::Core::Transform()), _openglQuad(new HMEngine::OpenGL::OpenGLQuad()),
	_quadTextures{ new HMEngine::OpenGL::UITexture(texturePath) }, _isAttachedToGameEngine(false), _isVisible(true)
{
	this->_currentTexture = _quadTextures[0];
	if (useVertices)
		this->_openglQuad->SetVertices(HMEngine::UI::Quad::rectangle);

	this->_quadDetails.position = position;
	this->_quadDetails.scale = scale;
	this->UpdateQuadDetails();

	this->UpdateTransform();
}

HMEngine::UI::Quad::Quad(const std::string& name, const glm::vec2& position, const glm::vec2& scale) : HMEngine::Core::EventObject(), _name(name),
_transform(new HMEngine::Core::Transform()), _isAttachedToGameEngine(false), _isVisible(true)
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

HMEngine::UI::Quad::Quad(const HMEngine::UI::Quad& other) : HMEngine::Core::EventObject(other), _name(other._name), _quadDetails(other._quadDetails),
_transform(new HMEngine::Core::Transform(*other._transform)), _isAttachedToGameEngine(false), _isVisible(true)
{
	for (auto& quadTexture : other._quadTextures)
	{
		this->_quadTextures.push_back(new HMEngine::OpenGL::UITexture(*quadTexture));
	}
	if (this->_quadTextures.size() > 0)
		this->_currentTexture = this->_quadTextures[0];

	if (other._openglQuad != nullptr)
		this->_openglQuad = new HMEngine::OpenGL::OpenGLQuad(*other._openglQuad);


	for (auto& child : other._childs)
	{
		this->_childs.push_back(child->Clone());
	}
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

		this->_isVisible = true;
		this->_openglQuad = new HMEngine::OpenGL::OpenGLQuad(*other._openglQuad);
		this->_transform = new HMEngine::Core::Transform(*other._transform);
		this->_name = other._name;
		this->_quadDetails = other._quadDetails;
		if (this->_isAttachedToGameEngine)
		{
			for (auto& quadTexture : other._quadTextures)
			{
				this->_quadTextures.push_back(new HMEngine::OpenGL::UITexture(*quadTexture));
			}
			if (this->_quadTextures.size() > 0)
				this->_currentTexture = this->_quadTextures[0];
		}

		for (auto& child : other._childs)
		{
			this->_childs.push_back(child->Clone());
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

void HMEngine::UI::Quad::SetTopLeft(const glm::vec2& topLeft)
{
	float width = this->_quadDetails.scale.x;
	float height = this->_quadDetails.scale.y;
	this->_quadDetails.width = width;
	this->_quadDetails.height = height;
	this->_quadDetails.topLeft = topLeft;
	this->_quadDetails.bottomRight = glm::vec2(topLeft.x + width, topLeft.y + height);
	this->_quadDetails.position = glm::vec2(topLeft.x + width / 2, topLeft.y + height / 2);

	this->UpdateTransform();
}

void HMEngine::UI::Quad::SetCenter(const glm::vec2& center)
{
	this->SetPosition(center);
}

inline void HMEngine::UI::Quad::Show()
{
	for (auto& child : this->_childs)
	{
		child->Show();
	}
	this->_isVisible = true;
	this->_isEnabled = true;
}

inline void HMEngine::UI::Quad::Hide()
{
	for (auto& child : this->_childs)
	{
		child->Hide();
	}
	this->_isVisible = false;
	this->_isEnabled = false;

}

inline void HMEngine::UI::Quad::SetVisiblity(bool isVisible)
{
	for (auto& child : this->_childs)
	{
		child->SetVisiblity(isVisible);
	}
	this->_isVisible = isVisible;
	this->_isEnabled = isVisible;

}

void HMEngine::UI::Quad::BindTexture() const
{
	this->_currentTexture->Bind();
}

void HMEngine::UI::Quad::Draw() const
{
	if (this->_isVisible && this->_currentTexture != nullptr)
	{
		if (this->_name == "AddGameObjectMenu")
		{
			int i = 0;
		}
		this->BindTexture();
		this->_openglQuad->Draw(GL_TRIANGLE_STRIP);
	}
}

void HMEngine::UI::Quad::AttachToGameEngine(HMEngine::GameEngine& gameEngine)
{
	this->_isAttachedToGameEngine = true;
	this->_gameEngine = &gameEngine;
	if (this->_openglQuad != nullptr)
		this->_openglQuad->Initialize();
	this->InitializeEventObject();
	for (auto& child : this->_childs)
	{
		this->_gameEngine->AddUI(child);
	}

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
	this->_quadDetails.topLeft = glm::vec2(this->_quadDetails.position.x - float(width) / 2,
		this->_quadDetails.position.y - float(height) / 2);
	this->_quadDetails.bottomRight = glm::vec2(this->_quadDetails.position.x + float(width) / 2,
		this->_quadDetails.position.y + float(height) / 2);

	this->UpdateTransform();
}