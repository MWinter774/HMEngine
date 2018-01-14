#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include "GameSettings.h"

namespace HMEngine
{
	namespace Core
	{
		class Transform;
		class GameObject;
		namespace Rendering
		{
			class Window;
			class RenderingEngine;
		}
	}

	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();

		void CreateNewWindow(unsigned int width, unsigned int height, const std::string& title, bool fullscreen);
		void Run();

		inline void LockCursor() const { HMEngine::GameSettings::SetIsCursorLocked(true); } //locks the cursor to the center of the window
		inline void UnlockCursor() const { HMEngine::GameSettings::SetIsCursorLocked(false); } //unlocks the cursor from the center of the window
		inline void SetSensitivity(float sensitivity) const { HMEngine::GameSettings::SetSensitivity(sensitivity); }
		inline void SetMouseVisible(bool isVisible) const { HMEngine::GameSettings::SetCursorVisible(isVisible); }

		void AddGameObject(const HMEngine::Core::GameObject& gameObject);

		inline std::vector<HMEngine::Core::GameObject*> GetGameObjects() { return this->_gameObjectsVector; };
		HMEngine::Core::GameObject* GetGameObject(const std::string& name);

		void RemoveGameObject(const std::string& name);

		void SetAmbientLight(const glm::vec3& ambientLight) const;
		void SetAmbientLight(float r, float g, float b) const;

	private:
		HMEngine::Core::Rendering::RenderingEngine* _renderingEngine;
		HMEngine::Core::Rendering::Window* _window;

		std::vector<HMEngine::Core::GameObject*> _gameObjectsToAddBuffer; //keeps track which game objects to add each iteration of the game loop
		std::vector<std::string> _gameObjectsToRemoveBuffer; //keeps track which game objects to delete each iteration of the game loop
		std::map<std::string, HMEngine::Core::GameObject*> _gameObjects; //maps between name of the game object to the game object itself
		std::vector<HMEngine::Core::GameObject*> _gameObjectsVector; //list of game objects(used to improve game engine's efficiency)

		void UpdateGameObjectsBuffers();
	};
}