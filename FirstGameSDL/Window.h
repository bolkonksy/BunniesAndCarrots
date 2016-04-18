#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include "Configuration.h"
#include <iostream>


class Window {
private:
	
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	int _screenWidth;
	int _screenHeight;

public:
	Window();
	bool init();
	void quit();
	int getWidth();
	int getHeight();
	SDL_Renderer* getRenderer();
	
};

#endif