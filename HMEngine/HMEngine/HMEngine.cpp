#include "HMEngine.h"

HMEngine::GameEngine::GameEngine()
{
}

HMEngine::GameEngine::~GameEngine()
{
}

/*
Runs the game.
*/
void HMEngine::GameEngine::Run()
{
	int numOfTime = ~0;
	while (!HMEngine::Core::Hardware::HardwareInputs::IsKeyTapped(SDLK_ESCAPE)) //temp
	{
		HMEngine::Core::Hardware::HardwareInputs::Update();
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyTapped(SDLK_w))
			std::cout << "Thats pretty good" << std::endl;
		numOfTime--;
	}
}