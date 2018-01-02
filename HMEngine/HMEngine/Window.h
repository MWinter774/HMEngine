#pragma once
#include <SDL2.0.7\SDL.h>
#undef main
#include <iostream>
#include <string>
#include <vector>

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
				void Update(std::vector<HMEngine::Core::GameObject>& objects);
				
			private:
				SDL_Window* _window;
				SDL_GLContext _context;
			};
		}
	}
}