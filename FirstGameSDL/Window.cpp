#include "Window.h"

Window::Window()
{
	_window = NULL;
	_renderer = NULL;
	_screenWidth = CFG::SCREEN_WIDTH;
	_screenHeight = CFG::SCREEN_HEIGHT;
}
bool Window::init()
{
	
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			std::cerr << SDL_GetError() << std::endl;
			return false;
		}

		_window = SDL_CreateWindow("Bunnies&Carrots", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_SHOWN);
		if (NULL == _window) {
			std::cerr << SDL_GetError() << std::endl;
			return false;
		}

		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED); /*| SDL_RENDERER_PRESENTVSYNC);*/
		if (NULL == _renderer) {
			std::cerr << SDL_GetError() << std::endl;
			return false;
		}

		SDL_ShowCursor(CFG::SHOW_CURSOR);
		SDL_SetRenderDrawColor(_renderer, 0xAB, 0xD0, 0x3F, 0xFF);



		return true;
}


int Window::getWidth()
{
	return _screenWidth;
}
int Window::getHeight()
{
	return _screenHeight;
}

SDL_Renderer* Window::getRenderer()
{
	return _renderer;
}

void Window::quit()
{
	
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	
}