#include <SDL2.0.7\SDL.h>
#include <iostream>

#undef main

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initialize SDL
	

	std::cout << "asdf" << std::endl;

	SDL_Quit(); //quit SDL, close everything
	system("pause");
	return 0;
}