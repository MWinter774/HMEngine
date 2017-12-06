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
		}
	}

	class GameEngine
	{
	public:
		static float GetFov() { return HMEngine::GameEngine::fovInDegrees; }
		static unsigned int GetWindowWidth() { return HMEngine::GameEngine::windowWidth; }
		static unsigned int GetWindowHeight() { return HMEngine::GameEngine::windowHeight; }
		static float GetZNear() { return HMEngine::GameEngine::zNear; }
		static float GetZFar() { return HMEngine::GameEngine::zFar; }

		GameEngine();
		~GameEngine();

		void CreateNewWindow(int width, int height, const std::string& title, bool fullscreen);
		void SetFov(float fovInDegrees);
		void SetZNear(float zNear);
		void SetZFar(float zFar);
		void Run();

		void AddGameObject(HMEngine::Core::GameObject gameObject);
		void RemoveGameObject(HMEngine::Core::GameObject gameObject);

	private:
		static float zNear;
		static float zFar;
		static float fovInDegrees;
		static unsigned int windowWidth;
		static unsigned int windowHeight;

		HMEngine::Core::Rendering::Window* _window;
		std::vector<HMEngine::Core::GameObject> _gameObjects;
	};
}