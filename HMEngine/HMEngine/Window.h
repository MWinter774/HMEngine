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
				Window(int width, int height, const std::string& title, bool fullscreen);
				~Window();
				void Update();
			private:
				SDL_Window* _window;
				SDL_GLContext _context;
			};
		}
	}
}