#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		class GameObject;
		namespace Rendering
		{
			class Window
			{
			public:
				Window(int width, int height, const std::string& title, bool fullscreen);
				~Window();
				void Update(std::vector<HMEngine::Core::GameObject> &objects);



			private:
				SDL_Window* _window;
				SDL_GLContext _context;
			};
		}
	}
}