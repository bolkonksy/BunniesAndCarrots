#ifndef FLOWER_SPEED
#define FLOWER_SPEED

#include "Flower.h"

class Flower_Speed : public Flower {
public:
	void init(Game* game, ResourceManager* rm, int id = 0, float spawnX = 0, float spawnY = 0);
};


#endif