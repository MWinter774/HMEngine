#include "GameEngine.h"

HMEngine::GameEngine::GameEngine() : _window(nullptr)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) //try to initialize SDL
	{
		std::cout << "SDL INITIALIZATION FAILED!" << std::endl;
		system("pause");
		return;
	}
	std::cout << "Succeeded initializing SDL..." << std::endl;
}

HMEngine::GameEngine::~GameEngine()
{
	if (this->_window != nullptr)
		delete this->_window;
	SDL_Quit();
}

void HMEngine::GameEngine::CreateNewWindow(int width, int height, const std::string& title, bool fullscreen)
{
	/* Updates the game settings */
	HMEngine::GameSettings::windowWidth = width;
	HMEngine::GameSettings::windowHeight = height;
	HMEngine::GameSettings::UpdateProjectionMatrix();

	_window = new HMEngine::Core::Rendering::Window(width, height, title, fullscreen);
}

/*
Runs the game.
*/
void HMEngine::GameEngine::Run()
{
	int count = 0;
	while (!HMEngine::Core::Hardware::HardwareInputs::IsKeyTapped(SDL_SCANCODE_ESCAPE)) //temp
	{
		HMEngine::Core::Hardware::HardwareInputs::Update(); //Updates inputs
		HMEngine::Core::Rendering::RenderingEngine::Render(this->_gameObjects); //Render objects

		/* Temporary key checking */
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyTapped(SDL_SCANCODE_W))
			std::cout << "w key is tapped" << std::endl;
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_S))
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

void HMEngine::GameEngine::AddGameObject(const HMEngine::Core::GameObject& gameObject)
{ 
	this->_gameObjects.push_back(gameObject); 
}

/*
void HMEngine::GameEngine::RemoveGameObject(const HMEngine::Core::GameObject& gameObject)
{
	this->_gameObjects.erase(std::remove(this->_gameObjects.begin(), this->_gameObjects.end(), gameObject), this->_gameObjects.end());
}
*/