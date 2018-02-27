#include "GameEngine.h"
#include "GameObject.h"
#include <SDL2.0.7\SDL.h>
#undef main
#include "RenderingEngine.h"
#include "Window.h"
#include "HardwareInputs.h"
#include "Transform.h"
#include "Camera.h"
#include "Utilities.h"
#include <algorithm>
#include "Quad.h"
#include "EventManager.h"
#include "Image.h"

HMEngine::GameEngine::GameEngine() : _window(nullptr), _renderingEngine(nullptr), _gameObjects(), _gameObjectsVector(), _gameObjectsToRemoveBuffer(), _camera(&HMEngine::Core::Rendering::Camera::GetInstance()), _quads(), _quadsToRemoveBuffer()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) //try to initialize SDL
	{
		HMEngine::Core::Utilities::ThrowException("SDL INITIALIZATION FAILED!");
	}
	HMEngine::Core::Utilities::PrintDebugMessage("Succeeded initializing SDL...");
}

HMEngine::GameEngine::~GameEngine()
{
	for (auto& gameObject : this->_gameObjects)
	{
		delete gameObject.second;
	}
	for (auto& quad : this->_quads)
	{
		delete quad.second;
	}
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

	this->_window = new HMEngine::Core::Rendering::Window(width, height, title, fullscreen);
	this->_renderingEngine = &HMEngine::Core::Rendering::RenderingEngine::GetInstance();
}

/*
Runs the game.
*/
void HMEngine::GameEngine::Run()
{
	if (this->_window == nullptr) //if user hasn't created a window yet
	{
		HMEngine::Core::Utilities::ThrowException("YOU NEED TO CREATE A WINDOW FIRST!!", "GameEngine Error");
	}
	HMEngine::GameSettings::SetCursorVisible(HMEngine::GameSettings::IsCursorVisible());
	HMEngine::Core::Hardware::HardwareInputs::SetCursorPos(HMEngine::GameSettings::GetWindowWidth() / 2, HMEngine::GameSettings::GetWindowHeight() / 2); //locks the mouse to the center of the screen

	Uint32 lastTime = SDL_GetTicks();
	Uint32 currTime = 0;
	int frames = 0;
	bool& calculateFPS = HMEngine::GameSettings::GetCalculateFPS();
	unsigned int windowWidth = HMEngine::GameSettings::GetWindowWidth();
	unsigned int windowHeight = HMEngine::GameSettings::GetWindowHeight();

	while (!HMEngine::Core::Hardware::HardwareInputs::IsKeyTapped(SDL_SCANCODE_ESCAPE)) //temp
	{
		if (calculateFPS)
		{
			currTime = SDL_GetTicks();
			frames++;
			if (currTime - lastTime >= 1000)
			{
				std::cout << 1000.0f / frames << std::endl;
				frames = 0;
				lastTime = currTime;
			}
		}
		this->UpdateGameObjectsBuffers();
		this->_camera->Update();

		HMEngine::Core::Hardware::HardwareInputs::Update(); //Updates inputs

		HMEngine::Core::EventManager::UpdateObjects();

		if (GameSettings::IsCursorLocked())
			HMEngine::Core::Hardware::HardwareInputs::SetCursorPos(windowWidth / 2, windowHeight / 2);

		this->_renderingEngine->Render(); //Render objects(on the second window buffer)
		this->_window->Update(); //Updates the window(swaps between the second window buffer and the first window buffer)
	}
}

/*
Copies the game object and adds the copy to the engine.
Input:
gameObject - the game object to clone and add
Output:
*/
void HMEngine::GameEngine::AddGameObject(const HMEngine::Core::GameObject& gameObject)
{
	if (this->_gameObjects.find(gameObject.GetName()) != this->_gameObjects.end()) //checkes if a game object with the same name exists
	{
		HMEngine::Core::Utilities::PrintDebugMessage("\"" + gameObject.GetName() + "\" Wasn't added because a game object with this name already exist!", "WARNING", 6);
		return;
	}
	auto go = gameObject.Clone();
	go->_gameEngine = this; //sets game object game engine to this
	go->AttachToGameEngine(); //activates event
	this->_gameObjects[go->GetName()] = go; //Adds game object to the game object map
	this->_gameObjectsVector.push_back(go); //Adds game object to the vector of game objects
}

/*
Adds game object to the engine.
Input:
gameObject - the game object to add
Output:
*/
void HMEngine::GameEngine::AddGameObject(HMEngine::Core::GameObject* gameObject)
{
	if (this->_gameObjects.find(gameObject->GetName()) != this->_gameObjects.end()) //checkes if a game object with the same name exists
	{
		HMEngine::Core::Utilities::PrintDebugMessage("\"" + gameObject->GetName() + "\" Wasn't added because a game object with this name already exist!", "WARNING", 6);
		return;
	}
	gameObject->_gameEngine = this; //sets game object game engine to this
	gameObject->AttachToGameEngine(); //activates event
	this->_gameObjects[gameObject->GetName()] = gameObject; //Adds game object to the game object map
	this->_gameObjectsVector.push_back(gameObject); //Adds game object to the vector of game objects
}

/*
Returns the game object using its name, if doesnt exist returns nullptr.
Input:
name - name of the game object.
Output:
nullptr if game object doesn't exist in the engine, else returns pointer to the game object.
*/
HMEngine::Core::GameObject* HMEngine::GameEngine::GetGameObject(const std::string& name)
{
	auto go = this->_gameObjects.find(name);
	if (go == this->_gameObjects.end()) //Game Object not found
	{
		HMEngine::Core::Utilities::PrintDebugMessage("\"" + name + "\" Game Object not found!", "ERROR", 4);
		return nullptr;
	}
	return (*go).second;
}

/*
Removes a game object from the game engine, throws an error if game object name doesn't exist in the engine.
Input:
name - name of the game object to remove.
Output:

*/
void HMEngine::GameEngine::RemoveGameObject(const std::string& name)
{
	auto go = this->_gameObjects.find(name);
	if (go == this->_gameObjects.end()) //Game Object not found
	{
		HMEngine::Core::Utilities::ThrowException("\"" + name + "\" GAME OBJECT NOT FOUND!");
	}
	this->_gameObjectsToRemoveBuffer.push_back(name);
}

void HMEngine::GameEngine::AddUI(const HMEngine::UI::Quad& ui)
{
	if (this->_quads.find(ui.GetName()) != this->_quads.end()) //checkes if a game object with the same name exists
	{
		HMEngine::Core::Utilities::PrintDebugMessage("\"" + ui.GetName() + "\" Wasn't added because a ui with this name already exist!", "WARNING", 6);
		return;
	}
	auto uiClone = ui.Clone();
	uiClone->InitializeEventObject();
	uiClone->AttachToGameEngine(*this);
	this->_quads[uiClone->GetName()] = uiClone; //adds the ui quad to the quad map
	this->_quadsVector.push_back(uiClone); //adds the quad to the quad vector
	this->_renderingEngine->AddUI(*uiClone);
}

void HMEngine::GameEngine::AddUI(HMEngine::UI::Quad* ui)
{
	if (this->_quads.find(ui->GetName()) != this->_quads.end()) //checkes if a game object with the same name exists
	{
		HMEngine::Core::Utilities::PrintDebugMessage("\"" + ui->GetName() + "\" Wasn't added because a ui with this name already exist!", "WARNING", 6);
		return;
	}

	ui->InitializeEventObject();
	ui->AttachToGameEngine(*this);
	this->_quads[ui->GetName()] = ui; //adds the ui quad to the quad map
	this->_quadsVector.push_back(ui); //adds the quad to the quad vector
	this->_renderingEngine->AddUI(*ui); //adds the quad to the rendering engine
}

HMEngine::UI::Quad* HMEngine::GameEngine::GetUI(const std::string& name)
{
	auto ui = this->_quads.find(name);
	if (ui == this->_quads.end()) //Game Object not found
	{
		HMEngine::Core::Utilities::PrintDebugMessage("\"" + name + "\" UI not found!", "ERROR", 4);
		return nullptr;
	}
	return (*ui).second;
}

void HMEngine::GameEngine::RemoveUI(const std::string& name)
{
	auto quad = this->_quads.find(name);
	if (quad == this->_quads.end()) //Game Object not found
	{
		HMEngine::Core::Utilities::ThrowException("\"" + name + "\" GAME OBJECT NOT FOUND!");
	}
	this->_quadsToRemoveBuffer.push_back(name);
}

glm::vec3 HMEngine::GameEngine::GetSkyColor() const
{
	return HMEngine::GameSettings::GetSkyColor();
}

void HMEngine::GameEngine::SetAmbientLight(const glm::vec3 & ambientLight) const
{
	HMEngine::GameSettings::SetAmbientLight(ambientLight);
}

void HMEngine::GameEngine::SetAmbientLight(float r, float g, float b) const
{
	HMEngine::GameSettings::ambientLight = glm::vec3(r, g, b);
}

void HMEngine::GameEngine::SetSkyColor(const glm::vec3& skyColor) const
{
	HMEngine::GameSettings::SetSkyColor(skyColor);
}

void HMEngine::GameEngine::SetSkyColor(float r, float g, float b) const
{
	HMEngine::GameSettings::SetSkyColor(glm::vec3(r, g, b));
}

void HMEngine::GameEngine::SetFogDensity(float fogDensity) const
{
	HMEngine::GameSettings::SetFogDensity(fogDensity);
}

void HMEngine::GameEngine::SetFogGradient(float fogGradient) const
{
	HMEngine::GameSettings::SetFogGradient(fogGradient);
}

void HMEngine::GameEngine::DisableFog() const
{
	HMEngine::GameSettings::SetFogDensity(0.0f);
}

void HMEngine::GameEngine::EnableFog() const
{
	HMEngine::GameSettings::SetFogDensity(0.0035f);
}

/*
Updates the buffers of game objects(handles adding/removing of game objects).
*/
void HMEngine::GameEngine::UpdateGameObjectsBuffers()
{
	/* Handles game object buffer */
	if (this->_gameObjectsToRemoveBuffer.size() > 0)
	{
		for (auto& gameObjectName : this->_gameObjectsToRemoveBuffer)
		{
			/* Remove Game Objects */
			this->_gameObjectsVector.erase(std::remove(this->_gameObjectsVector.begin(), this->_gameObjectsVector.end(), this->_gameObjects[gameObjectName]), this->_gameObjectsVector.end()); //deletes the game object from the list of game objects
			delete this->_gameObjects[gameObjectName]; //frees the memory of the game object
			this->_gameObjects.erase(gameObjectName); //deletes the game object name for the map of names and game objects
		}
		this->_gameObjectsToRemoveBuffer.clear(); //clears the buffer
	}

	/* Handles quads buffer */
	if (this->_quadsToRemoveBuffer.size() > 0)
	{
		for (auto& quadName : this->_quadsToRemoveBuffer)
		{
			this->_quadsVector.erase(std::remove(this->_quadsVector.begin(), this->_quadsVector.end(), this->_quads[quadName]), this->_quadsVector.end()); //deletes the quad from the list of game objects
			this->_renderingEngine->RemoveUI(*this->_quads[quadName]);
			delete this->_quads[quadName]; //frees the memory of the game object
			this->_quads.erase(quadName); //deletes the game object name for the map of names and game objects
		}
		this->_quadsToRemoveBuffer.clear(); //clears the buffer
	}
}