#include "MainPlayer.h"
#include "GameEngine.h"
#include "GameSettings.h"
#include "Ray.h"
#include "Camera.h"
#include "PhysicsEngine.h"
#include "Fonts.h"

MainPlayer::MainPlayer(const std::string& name, float walkingSpeed, float runningSpeed, float maxJumpHeight) :
	HMEngine::PhysicalPlayer(name + "_physicalPlayer", walkingSpeed, runningSpeed, maxJumpHeight), _ammo(30)
{
	this->InitializeEvents<MainPlayer>(this);
	this->_attachToGameEngineEvents.push_back(std::bind(&MainPlayer::AddObjects, this));
	this->_updateEvents.push_back(std::bind(&MainPlayer::MyUpdate, this));
	this->_mouseDownEvents.push_back(std::bind(&MainPlayer::Shoot, this, std::placeholders::_1));
}

MainPlayer::~MainPlayer()
{
}

void MainPlayer::MyUpdate()
{

}

bool MainPlayer::GotHit(float damageInPercentage)
{
	this->_pbHealthBar->DecreaseBar(damageInPercentage);

	return this->_pbHealthBar->GetPercentage() <= 0.0f;
}

void MainPlayer::SetHealth(float percentage)
{
	this->_pbHealthBar->SetPercentage(percentage);
}

void MainPlayer::Shoot(const unsigned int& mouseButton)
{
	if (mouseButton == SDL_BUTTON_LEFT && this->_ammo > 0)
	{
		this->_ammo--;
		HMEngine::Core::Physics::Ray ray = HMEngine::Core::Rendering::Camera::GetInstance().GetRayFromScreenPoint(HMEngine::GameSettings::GetScreenCenter());
		auto k = HMEngine::Core::Physics::PhysicsEngine::Raycast(ray);
		if (k)
		{
			for (auto& e : this->_shootEvent)
				e(k);
		}
		this->_lblAmmo->SetText(std::to_string(this->_ammo));
	}
}

void MainPlayer::SetAmmo(unsigned int ammo)
{
	this->_ammo = ammo;
	this->_lblAmmo->SetText(std::to_string(this->_ammo));
}

void MainPlayer::AddObjects()
{
	this->_pbHealthBar = new HMEngine::UI::ProgressBar("pbMainPlayerHealth", HMEngine::GameSettings::GetScreenCenter() - glm::vec2(0, 320),
		glm::vec2(600, 50), "./resources/UITextures/progressBarBackground.png", "./resources/UITextures/progressBarBarTexture.png",
		100, false);
	this->_lblAmmo = new HMEngine::UI::Label("lblMainPlayerAmmo", glm::vec2(80, 680), std::to_string(this->_ammo),
		HMEngine::Fonts::ARIAL, glm::vec3(), 4.0f);

	this->_gameEngine->AddUI(this->_pbHealthBar);
	this->_gameEngine->AddUI(this->_lblAmmo);
}