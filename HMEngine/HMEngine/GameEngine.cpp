#include "GameEngine.h"
#include "GameObject.h"
#include <SDL2.0.7\SDL.h>
#undef main
#include "RenderingEngine.h"
#include "Window.h"
#include "HardwareInputs.h"
#include "Transform.h"
#include "Camera.h"

HMEngine::GameEngine::GameEngine() : _window(nullptr), _renderingEngine(&HMEngine::Core::Rendering::RenderingEngine::GetInstance())
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

void HMEngine::GameEngine::CreateNewWindow(unsigned int width, unsigned int height, const std::string& title, bool fullscreen)
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
	HMEngine::GameSettings::SetCursorVisible(HMEngine::GameSettings::IsCursorVisible());
	HMEngine::Core::Hardware::HardwareInputs::SetCursorPos(HMEngine::GameSettings::GetWindowWidth() / 2, HMEngine::GameSettings::GetWindowHeight() / 2); //locks the mouse to the center of the screen

	Uint32 lastTime = SDL_GetTicks();
	Uint32 currTime = 0;
	int frames = 0;
	bool& calculateFPS = HMEngine::GameSettings::GetCalculateFPS();

	while (!HMEngine::Core::Hardware::HardwareInputs::IsKeyTapped(SDL_SCANCODE_ESCAPE)) //temp
	{
		if (calculateFPS)
		{
			currTime = SDL_GetTicks();
			frames++;
			if (currTime - lastTime >= 1000)
			{
				std::cout << frames << std::endl;
				frames = 0;
				lastTime = currTime;
			}
		}

		HMEngine::Core::Hardware::HardwareInputs::Update(); //Updates inputs

		for (auto& gameObject : this->_gameObjects)
		{
			gameObject.Update();
		}
		if (GameSettings::IsCursorLocked())
			HMEngine::Core::Hardware::HardwareInputs::SetCursorPos(HMEngine::GameSettings::GetWindowWidth() / 2, HMEngine::GameSettings::GetWindowHeight() / 2);

		this->_renderingEngine->Render(this->_gameObjects); //Render objects(on the second window buffer)
		this->_window->Update(); //Updates the window(swaps between the second window buffer and the first window buffer)
	}

}

void HMEngine::GameEngine::AddGameObject(const HMEngine::Core::GameObject& gameObject)
{
	this->_gameObjects.push_back(gameObject);
}

void HMEngine::GameEngine::SetAmbientLight(const glm::vec3 & ambientLight) const
{
	HMEngine::GameSettings::ambientLight = ambientLight;
}

void HMEngine::GameEngine::SetAmbientLight(float r, float g, float b) const
{
	HMEngine::GameSettings::ambientLight = glm::vec3(r, g, b);
}

/*
void HMEngine::GameEngine::RemoveGameObject(const HMEngine::Core::GameObject& gameObject)
{
	this->_gameObjects.erase(std::remove(this->_gameObjects.begin(), this->_gameObjects.end(), gameObject), this->_gameObjects.end());
}
*/