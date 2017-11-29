#include "HMEngineIncludes.h"

int main()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //initialize SDL
	{
		std::cout << "Succeeded initializing SDL..." << std::endl;

		std::string title = "test";
		HMEngine::Core::Rendering::Render display(800, 600, title, 0); //create window
		HMEngine::GameEngine g;
		//while (display.GetIsRunning()) //update window while its running
		//{
			//display.update();
		//}
		
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