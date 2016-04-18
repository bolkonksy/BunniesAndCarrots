#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>

#include "Configuration.h"
#include "Stats.h"
#include "Window.h"

class GameState;

class Game {
private:
	Window _window;
	//SDL_Renderer* _renderer;
	SDL_Event _event;

	//int _screenWidth;
	//int _screenHeight;

	/* Stack for gamestates */
	std::vector<GameState*> _states;

	/* Controling frame rate */
	Uint32 _newTime;
	Uint32 _oldTime;

	/* So all states could have access to stats */
	Stats* _stats;

	bool _quit;

public:
	Game();
	
	bool init(GameState*);
	void thread();

	void pushState(GameState*);
	void popState();

	void setQuit();
	SDL_Renderer* getRenderer();

	int getWidth();
	int getHeight();

	GameState* getState();

	Stats* getStats();

private:
	/* Internal loop functions */
	void update();
	void render();
	void quit();
};


#endif