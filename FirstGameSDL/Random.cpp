#include "Random.h"

#include <stdlib.h>
#include <time.h>

int Random::randNumber(int lower, int upper)
{
	static unsigned int random = 0;
	srand((unsigned int)time(NULL) + random);
	random = rand();

	if (lower > upper) {
		int tmp = lower;
		lower = upper;
		upper = tmp;
	}

	return (rand() % (upper - lower + 1)) + lower;
}

float Random::randNumber(float lower, float upper)
{
	static unsigned int random = 0;
	srand((unsigned int)time(NULL) + random);
	random = rand();

	if (lower > upper) {
		int tmp = (int)lower;
		lower = upper;
		upper = (float)tmp;
	}

	return (float)(rand() % ((int)upper - (int)lower + 1)) + lower;
}