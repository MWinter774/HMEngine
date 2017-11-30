#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		namespace Rendering
		{
			class Window
			{
			public:
				Window(int width, int height, std::string& title, bool fullscreen);
				~Window();
				void update();
				bool GetIsRunning() { return isRunning; };
			private:
				SDL_Window* window;
				SDL_GLContext context;

				bool isRunning;
			};
		}
	}
}