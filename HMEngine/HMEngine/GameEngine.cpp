#include "GameEngine.h"

float HMEngine::GameEngine::zNear = 0.1f;
float HMEngine::GameEngine::zFar = 1000.0f;
float HMEngine::GameEngine::FovInDegrees = 45.0f;
unsigned int HMEngine::GameEngine::windowWidth = 800U;
unsigned int HMEngine::GameEngine::windowHeight = 600U;

HMEngine::GameEngine::GameEngine() : _window(nullptr)
{
}

HMEngine::GameEngine::~GameEngine()
{
	if (this->_window != nullptr)
		delete this->_window;
}

void HMEngine::GameEngine::CreateNewWindow(int width, int height, const std::string& title, bool fullscreen)
{
	HMEngine::GameEngine::windowWidth = width;
	HMEngine::GameEngine::windowHeight = height;
	_window = new HMEngine::Core::Rendering::Window(width, height, title, fullscreen);
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