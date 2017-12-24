#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		class GameObject;
		namespace Rendering
		{

			namespace Shaders
			{
				class BasicShader;
			}
			class Window
			{
			public:
				Window(int width, int height, const std::string& title, bool fullscreen);
				~Window();
				 void Update(GLuint shaderProgram, std::vector<GameObject> objects, glm::mat4 mvp);
			private:
				 SDL_Window* _window;
				 SDL_GLContext _context;
			};
		}
	}
}