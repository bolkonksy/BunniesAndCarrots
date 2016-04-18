#ifndef FLOWER_DEAD
#define FLOWER_DEAD

#include "Flower.h"

class Flower_Dead : public Flower {
public:
	void init(Game* game, ResourceManager* rm, int id = 0, float spawnX = 0, float spawnY = 0);

};


#endif