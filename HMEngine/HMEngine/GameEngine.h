#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core::Rendering
	{
		class Window;
	}
	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();

		void CreateNewWindow(int width, int height, std::string& title, bool fullscreen);
		void Run();

	private:
		HMEngine::Core::Rendering::Window* _window;
	};
}