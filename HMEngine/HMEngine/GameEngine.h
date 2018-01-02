#pragma once
#include <iostream>
#include <vector>
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

		void CreateNewWindow(int width, int height, const std::string& title, bool fullscreen);
		void Run();

		inline void LockCursor() const { HMEngine::GameSettings::SetIsCursorLocked(true); } //locks the cursor to the center of the window
		inline void UnlockCursor() const { HMEngine::GameSettings::SetIsCursorLocked(false); } //unlocks the cursor from the center of the window
		inline void SetSensitivity(float sensitivity) const { HMEngine::GameSettings::SetSensitivity(sensitivity); }
		inline void SetMouseVisible(bool isVisible) const { HMEngine::GameSettings::SetCursorVisible(isVisible); }

		void AddGameObject(const HMEngine::Core::GameObject& gameObject);

	private:
		HMEngine::Core::Rendering::RenderingEngine* _renderingEngine;
		HMEngine::Core::Rendering::Window* _window;
		std::vector<HMEngine::Core::GameObject> _gameObjects;
	};
}