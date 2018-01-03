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

		void CreateNewWindow(unsigned int width, unsigned int height, const std::string& title, bool fullscreen);
		void Run();

		void AddGameObject(const HMEngine::Core::GameObject& gameObject);

		void SetAmbientLight(const glm::vec3& ambientLight) const;
		void SetAmbientLight(float r, float g, float b) const;

	private:
		HMEngine::Core::Rendering::RenderingEngine* _renderingEngine;
		HMEngine::Core::Rendering::Window* _window;
		std::vector<HMEngine::Core::GameObject> _gameObjects;

	};
}