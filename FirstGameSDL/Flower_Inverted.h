#ifndef FLOWER_INVERTED
#define FLOWER_INVERTED

#include "Flower.h"

class Flower_Inverted : public Flower {
public:
	void init(Game* game, ResourceManager* rm, int id = 0, float spawnX = 0, float spawnY = 0);
};


#endif