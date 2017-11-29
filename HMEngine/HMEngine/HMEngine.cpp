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
	int count = 0;
	while (!HMEngine::Core::Hardware::HardwareInputs::IsKeyTapped(SDLK_ESCAPE)) //temp
	{
		HMEngine::Core::Hardware::HardwareInputs::Update();
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyTapped(SDLK_w))
			std::cout << "w key is tapped" << std::endl;
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDLK_s))
			std::cout << "s key is held down" << std::endl;
		if (HMEngine::Core::Hardware::HardwareInputs::IsMouseButtonDown(SDL_BUTTON_LEFT))
			std::cout << "left mouse button is held down" << std::endl;
		if (HMEngine::Core::Hardware::HardwareInputs::IsMouseButtonTapped(SDL_BUTTON_RIGHT))
			std::cout << "right mouse button is tapped" << std::endl;
		if (count % 500000 == 0)
		{
			std::cout << HMEngine::Core::Hardware::HardwareInputs::GetCursorXPos() << ", " << HMEngine::Core::Hardware::HardwareInputs::GetCursorYPos() << std::endl;
			count = 0;
		}
		count++;
	}
}