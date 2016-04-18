#ifndef OBJECT_H
#define OBJECT_H

#include "Game.h"
#include "ResourceManager.h"

class Object {
protected:
	/* So every object could have its index/id */
	int _id;

	/* Object position - coordinates */
	float _x, _y;

	/* Frame sizes */
	float _sizeX, _sizeY;

	/* Distance from window border */
	float _border_x1;
	float _border_x2;
	float _border_y1;
	float _border_y2;

	/* Rects for rendering */
	SDL_Rect _destRect, _srcRect;

	/* For renderer and loading textures */
	Game* _game;
	ResourceManager* _rm;

public:
	virtual void init(Game* game, ResourceManager* rm, int id, float spawnX, float spawnY) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

	bool collideWith(Object* other);
};


#endif