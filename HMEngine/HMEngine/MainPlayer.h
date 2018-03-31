#pragma once
#include "glm\glm.hpp"
#include <string>
#include "PhysicalPlayer.h"
#include "ProgressBar.h"
#include "RaycastInfo.h"
#include <functional>
#include "Label.h"

class MainPlayer : public HMEngine::PhysicalPlayer
{
public:
	std::vector<std::function<void(HMEngine::Core::Physics::RaycastInfo&)>> _shootEvent;

	MainPlayer(const std::string& name, float walkingSpeed = 5.0f, float runningSpeed = 10.0f, float maxJumpHeight = 5.0f);
	~MainPlayer();

	void MyUpdate();
	bool GotHit(float damageInPercentage);
	void SetHealth(float percentage);
	void Shoot(const unsigned int& mouseButton);

private:
	unsigned int _ammo;
	HMEngine::UI::ProgressBar* _pbHealthBar;
	HMEngine::UI::Label* _lblAmmo;

	void AddObjects();
};

