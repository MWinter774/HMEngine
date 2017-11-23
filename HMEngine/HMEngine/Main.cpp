#include <SDL2.0.7\SDL_opengl.h>
#include <iostream>

#undef main

int main()
{
	glBegin(0);

	std::cout << "asdf" << std::endl;
	glEnd();

	system("pause");
	return 0;
}