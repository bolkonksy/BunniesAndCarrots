#ifndef FLOWER_H
#define FLOWER_H

#include "Object.h"

class Flower : public Object {
protected:
	SDL_Texture* _texture;

public:
	/* Atm id is irrelevant */
	virtual void init(Game* game, ResourceManager* rm, int id, float spawnX, float spawnY) = 0;
	void update(float deltaTime = 0.0f);
	void render();
	void spawn(bool noRespawn = false);
};


#endif