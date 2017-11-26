#ifndef Render_H
#define Render_H

#include <iostream>
#include <string>
#include <SDL2.0.7\SDL.h>

#pragma once

class Render
{
public:
	Render(int width, int height, std::string& title, bool fullscreen);
	~Render();
	void update();
	bool GetIsRunning() { return isRunning; };
private:
	SDL_Window* window;
	SDL_GLContext context;

	bool isRunning;

};


#endif // !Render_H
