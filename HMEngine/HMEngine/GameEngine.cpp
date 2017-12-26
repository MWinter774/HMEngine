#include "GameEngine.h"

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
		this->_renderingEngine->Render(this->_gameObjects); //Render objects

		/* Temporary key checking */
		float speed = 0.05f;
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_W))
		{
			HMEngine::Core::Rendering::Camera::GetInstance().AddPositionY(-speed);
		}
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_S))
		{
			HMEngine::Core::Rendering::Camera::GetInstance().AddPositionY(speed);
		}
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_A))
		{
			HMEngine::Core::Rendering::Camera::GetInstance().AddPositionX(-speed);
		}
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_D))
		{
			HMEngine::Core::Rendering::Camera::GetInstance().AddPositionX(speed);
		}
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_Q))
		{
			HMEngine::Core::Rendering::Camera::GetInstance().AddPositionZ(speed);
		}
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_E))
		{
			HMEngine::Core::Rendering::Camera::GetInstance().AddPositionZ(-speed);
		}
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_LEFT))
		{
			this->_gameObjects[0].GetTransform().AddRotationY(-speed);
		}
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_RIGHT))
		{
			this->_gameObjects[0].GetTransform().AddRotationY(speed);
		}
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_UP))
		{
			this->_gameObjects[0].GetTransform().AddRotationX(speed);
		}
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_DOWN))
		{
			this->_gameObjects[0].GetTransform().AddRotationX(-speed);
		}



		if (HMEngine::Core::Hardware::HardwareInputs::IsMouseButtonDown(SDL_BUTTON_LEFT))
			std::cout << "left mouse button is held down" << std::endl;
		if (HMEngine::Core::Hardware::HardwareInputs::IsMouseButtonTapped(SDL_BUTTON_RIGHT))
			std::cout << "right mouse button is tapped" << std::endl;


		if (count % 500 == 0)
		{
			std::cout << HMEngine::Core::Hardware::HardwareInputs::GetCursorXPos() << ", " << HMEngine::Core::Hardware::HardwareInputs::GetCursorYPos() << std::endl;
			count = 0;
		}
		//system("cls");
		//std::cout << glm::to_string(HMEngine::Core::Rendering::Camera::GetInstance().GetPosition()) << std::endl;
		//std::cout << glm::to_string(HMEngine::Core::Rendering::Camera::GetInstance().GetPosition()) << std::endl;
	
		count++;

		this->_window->Update(this->_gameObjects);
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