#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <SDL2.0.7\SDL.h>

#pragma once

class Display
{
public:
	Display(int width, int height, std::string& title);
	~Display();

private:
	SDL_Window* window;

};


#endif // !DISPLAY_H
