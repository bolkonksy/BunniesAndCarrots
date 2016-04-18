#ifndef CARROT_H
#define CARROT_H

#include "Object.h"

class Carrot : public Object {
private:
	SDL_Texture* _texture;

	float _carrotFrame;

public:
	/* Atm id is irrelevant */
	void init(Game* game, ResourceManager* rm, int id = 0, float spawnX = 0, float spawnY = 0);
	void update(float deltaTime);
	void render();

	void relocate();
};


#endif