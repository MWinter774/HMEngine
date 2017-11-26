#include <SDL2.0.7\SDL.h>
#include <iostream>
#include "Render.h"
#undef main

int main()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //initialize SDL
	{
		std::cout << "Succeeded initializing SDL..." << std::endl;

		std::string title = "test";
		Render display(800, 600, title, 0); //create window
		while (display.GetIsRunning()) //update window while its running
		{
			display.update();
		}
		
		SDL_Quit(); //quit SDL, close everything
	}
	else
	{
		std::cout << "Failed to initialize SDL..." << std::endl;
		system("pause");
	}
	return 0;
}