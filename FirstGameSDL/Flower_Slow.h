#ifndef FLOWER_SLOW
#define FLOWER_SLOW

#include "Flower.h"

class Flower_Slow : public Flower {
public:
	void init(Game* game, ResourceManager* rm, int id = 0, float spawnX = 0, float spawnY = 0);

};


#endif