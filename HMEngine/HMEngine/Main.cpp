#include "HMEngineIncludes.h"

int main()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //initialize SDL
	{
		std::cout << "Succeeded initializing SDL..." << std::endl;

		std::string title = "test";

		HMEngine::GameEngine g;
		g.CreateNewWindow(800, 600, title, false);
		
		g.Run();
		SDL_Quit(); //quit SDL, close everything
	}
	else
	{
		std::cout << "Failed to initialize SDL..." << std::endl;
		system("pause");
	}
	return 0;
}