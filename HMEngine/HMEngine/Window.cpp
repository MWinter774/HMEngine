#include "Window.h"
#include <GL\glew.h>
#include <SDL2.0.7\SDL.h>
#undef main
#include <iostream>
#include <string>
#include <vector>
#include "HardwareInputs.h"

/*
This function creates the game's window
int width  - The width of the window
int height - The height of the window
std::string& title - The name\title of the window
bool fullscreen - Whether to open the window in fullscreen or windowed, fullscreen ignores the width and height values

*/
HMEngine::Core::Rendering::Window::Window(int width, int height, const std::string& title, bool fullscreen)
{
	Uint32 flags = SDL_WINDOW_OPENGL;
	if (fullscreen)
	{
		flags |= SDL_WINDOW_FULLSCREEN;
	}
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetSwapInterval(1);

	_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	_context = SDL_GL_CreateContext(_window);
	
	HMEngine::Core::Hardware::HardwareInputs::SetWindow(this->_window);

	std::cout << glGetString(GL_VERSION) << std::endl;

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize!" << std::endl;
	}
}

/*
This function destroys the window and its context
*/
HMEngine::Core::Rendering::Window::~Window()
{
	SDL_GL_DeleteContext(_context);
	SDL_DestroyWindow(_window);
}

/*
This function updates the window by swapping it with the 2nd window buffer
*/
void HMEngine::Core::Rendering::Window::Update()
{
	SDL_GL_SwapWindow(_window);
}