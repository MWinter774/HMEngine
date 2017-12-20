#pragma once
#include "HMEngineIncludes.h"

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

		void AddGameObject(const HMEngine::Core::GameObject& gameObject);

	private:
		HMEngine::Core::Rendering::Window* _window;
		std::vector<HMEngine::Core::GameObject> _gameObjects;
	};
}