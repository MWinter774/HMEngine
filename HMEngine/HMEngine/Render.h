#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		namespace Rendering
		{
			class Render
			{
			public:
				Render(int width, int height, std::string& title, bool fullscreen);
				~Render();
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