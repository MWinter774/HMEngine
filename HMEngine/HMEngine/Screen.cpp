#include "Screen.h"
#include "QuadCollection.h"
#include "SDL2.0.7\SDL.h"
#include "HardwareInputs.h"
#include "Image.h"
#include "GameEngine.h"
#include <algorithm>

HMEngine::UI::Screen::Screen(const std::string& screenName, const glm::vec2& centerPos, const glm::vec2& scale) :
	HMEngine::UI::Quad(screenName, centerPos, scale), _screen(new HMEngine::UI::QuadCollection(screenName + "_quadCollection", centerPos, glm::vec2()))
{
	this->InitializeEvents<Screen>(this);
	this->Show();
}

HMEngine::UI::Screen::~Screen()
{
}

HMEngine::UI::Screen::Screen(const HMEngine::UI::Screen& other) : HMEngine::UI::Quad(other)
{
	this->InitializeEvents<Screen>(this);
	this->_screen = new HMEngine::UI::QuadCollection(*other._screen);
}

HMEngine::UI::Screen& HMEngine::UI::Screen::operator=(const HMEngine::UI::Screen& other)
{
	if (this != &other)
	{
		delete this->_screen;

		HMEngine::UI::Quad::operator=(other);
		this->_screen = new HMEngine::UI::QuadCollection(*other._screen);
	}

	return *this;
}

void HMEngine::UI::Screen::SetBackground(const std::string& backgroundTextureFilePath)
{
	HMEngine::UI::Image* img = new HMEngine::UI::Image(this->_name + "_background", backgroundTextureFilePath, this->_quadDetails.position, this->_quadDetails.scale);
	this->AddChild(0, img);
}

void HMEngine::UI::Screen::AddQuad(HMEngine::UI::Quad* quad)
{
	if (auto subScreen = dynamic_cast<HMEngine::UI::Screen*>(quad))
		this->_subScreens.push_back(subScreen);
	this->AddChild(quad);
}

bool HMEngine::UI::Screen::IsFocused() const
{
	for (auto& subScreen : this->_subScreens)
	{
		if (subScreen->IsVisible())
			return true;
	}
	return false;
}

void HMEngine::UI::Screen::MouseButtonDownEvent(const unsigned int& mouseButton)
{
	if (mouseButton == SDL_BUTTON_LEFT && !this->IsFocused() && !HMEngine::Core::Hardware::HardwareInputs::IsCursorWithinBoundaries(this->_quadDetails.topLeft, this->_quadDetails.bottomRight))
	{
		this->Hide();
	}
}

void HMEngine::UI::Screen::AttachToGameEngine(HMEngine::GameEngine& gameEngine)
{
	this->_isAttachedToGameEngine = true;
	this->_gameEngine = &gameEngine;
	if (this->_openglQuad != nullptr)
		this->_openglQuad->Initialize();
	this->InitializeEventObject();
	for (auto& child : this->_childs)
	{
		child->AttachToGameEngine(gameEngine);
	}
	gameEngine.AddScreen(this);

	this->AttachToGameEngineEvent();
}

void HMEngine::UI::Screen::Show()
{
	if (!this->_isVisible)
	{
		this->_gameEngine->AddActiveScreen(this);
		for (auto& child : this->_childs)
		{
			child->Show();
		}
		this->ShowEvent();
		this->_isVisible = true;
		this->_isEnabled = true;
	}
}

void HMEngine::UI::Screen::Hide()
{
	if (this->_isVisible)
	{
		for (auto& child : this->_childs)
		{
			child->Hide();
		}
		if (this->_hideEvent)
			this->_hideEvent();
		this->HideEvent();
		this->_isVisible = false;
		this->_isEnabled = false;
		if (this->_gameEngine != nullptr)
			this->_gameEngine->RemoveActiveScreen(this);
	}
}

void HMEngine::UI::Screen::SetVisiblity(bool isVisible)
{
	/*for (auto& child : this->_childs)
	{
		child->SetVisiblity(isVisible);
	}
	if (isVisible)
		this->ShowEvent();
	else
		this->HideEvent();
	this->_isVisible = isVisible;
	this->_isEnabled = isVisible;*/
	if (isVisible)
		this->Show();
	else
		this->Hide();
}
