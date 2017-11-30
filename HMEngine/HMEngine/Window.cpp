#include "Window.h"

/*
This function creates the game's window
int width  - The width of the window
int height - The height of the window
std::string& title - The name\title of the window
bool fullscreen - Whether to open the window in fullscreen or windowed, fullscreen ignores the width and height values

*/
HMEngine::Core::Rendering::Window::Window(int width, int height, std::string& title, bool fullscreen)
{
	isRunning = true;
	Uint32 flags = SDL_WINDOW_OPENGL;
	if (fullscreen)
	{
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	}
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	context = SDL_GL_CreateContext(window);
}

/*
This function destroys the window and its context
*/
HMEngine::Core::Rendering::Window::~Window()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

/*
This function updates the window by swapping it with the 2nd window buffer, and checks for events
*/
void HMEngine::Core::Rendering::Window::update()
{
	SDL_GL_SwapWindow(window);

	
}