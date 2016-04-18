#ifndef LEVEL_H
#define LEVEL_H

#include <sstream> 

#include "Game.h"
#include "ResourceManager.h"
#include "Font.h"
#include "Timer.h"


#define LEVEL_WIDTH 50
#define LEVEL_HEIGHT 38
#define TILE_SIZE 16

class Level {
private:
	SDL_Texture* _map;
	Font* _font;
	Game* _game;
	ResourceManager* _rm;
	Timer* _timer;

	/* These are declared here. They are used for displaying score */
	std::string _P1text;
	std::string _P2text;
	std::string _textTime;
	std::string _lifeLeft;

	/* For converting timer time to string easily */
	std::stringstream _gameplayTime;


public:
	Level(Game* game, ResourceManager* rm, Timer* timer);
	~Level();

	void init();
	void render();
};


#endif