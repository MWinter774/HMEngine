#include "HMEngineIncludes.h"

int main()
{
	std::string title = "test";

	HMEngine::GameEngine g;
	g.CreateNewWindow(800, 600, title, false);
	
	g.Run();

	

	return 0;
}