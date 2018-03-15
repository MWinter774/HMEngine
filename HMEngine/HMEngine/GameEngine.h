#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include "GameSettings.h"

namespace HMEngine
{
	namespace UI
	{
		class Quad;
		class Screen;
	}
	namespace Core
	{
		class Transform;
		class GameObject;
		namespace Rendering
		{
			class Window;
			class Camera;
			class RenderingEngine;
		}
	}

	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();
		GameEngine(const HMEngine::GameEngine& other) = delete;
		HMEngine::GameEngine& operator=(const HMEngine::GameEngine& other) = delete;

		void CreateNewWindow(unsigned int width, unsigned int height, const std::string& title, bool fullscreen);
		void Run();

		inline void LockCursor() const { HMEngine::GameSettings::SetIsCursorLocked(true); } //locks the cursor to the center of the window
		inline void UnlockCursor() const { HMEngine::GameSettings::SetIsCursorLocked(false); } //unlocks the cursor from the center of the window
		inline void SetSensitivity(float sensitivity) const { HMEngine::GameSettings::SetSensitivity(sensitivity); }
		inline void SetMouseVisible(bool isVisible) const { HMEngine::GameSettings::SetCursorVisible(isVisible); }

		void AddGameObject(const HMEngine::Core::GameObject& gameObject);
		void AddGameObject(HMEngine::Core::GameObject* gameObject);
		inline std::vector<HMEngine::Core::GameObject*> GetGameObjects() { return this->_gameObjectsVector; }
		HMEngine::Core::GameObject* GetGameObject(const std::string& name);
		void RemoveGameObject(const std::string& name);

		void AddUI(const HMEngine::UI::Quad& ui);
		void AddUI(HMEngine::UI::Quad* ui);
		inline std::vector<HMEngine::UI::Quad*> GetUIs() { return this->_quadsVector; };
		HMEngine::UI::Quad* GetUI(const std::string& name);
		void RemoveUI(const std::string& name);

		bool IsNameAvailable(const std::string& name);

		glm::vec3 GetSkyColor() const;

		void SetAmbientLight(const glm::vec3& ambientLight) const;
		void SetAmbientLight(float r, float g, float b) const;
		void SetSkyColor(const glm::vec3& skyColor) const;
		void SetSkyColor(float r, float g, float b) const;
		void SetFogDensity(float fogDensity) const;
		void SetFogGradient(float fogGradient) const;
		void DisableFog() const;
		void EnableFog() const;
		void EnableFPSCalculating() const;
		void DisableFPSCalculating() const;

		void InitializeWorldEditor(unsigned int width, unsigned int height, const std::string& title, bool fullscreen);

	private:
		HMEngine::Core::Rendering::RenderingEngine* _renderingEngine;
		HMEngine::Core::Rendering::Window* _window;
		HMEngine::Core::Rendering::Camera* _camera;

		std::map<std::string, HMEngine::Core::GameObject*> _gameObjects; //maps between name of the game object to the game object itself
		std::vector<std::string> _gameObjectsToRemoveBuffer; //keeps track which game objects to delete each iteration of the game loop
		std::vector<HMEngine::Core::GameObject*> _gameObjectsVector; //list of game objects(used to improve game engine's efficiency)
		
		std::map<std::string, HMEngine::UI::Quad*> _quads;
		std::vector<std::string> _quadsToRemoveBuffer;
		std::vector<HMEngine::UI::Quad*> _quadsVector;
		std::vector<HMEngine::UI::Screen*> _screens;

		void UpdateGameObjectsBuffers();
	};
}