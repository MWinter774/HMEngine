#include "Window.h"

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
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	}
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	_context = SDL_GL_CreateContext(_window);
	
	std::cout << glGetString(GL_VERSION) << std::endl;

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize!" << std::endl;
	}

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);

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
This function updates the window by swapping it with the 2nd window buffer, and checks for events
*/
void HMEngine::Core::Rendering::Window::Update(std::vector<HMEngine::Core::GameObject> &objects)
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << err << std::endl;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& object : objects)
	{
		HMEngine::Core::Rendering::Shaders::BasicShader::GetInstance().UpdateUniforms(object.GetTransform());

		for (auto& c : object.GetComponents())
		{
			c->Render();
		}
	}
	
	SDL_GL_SwapWindow(_window);

}