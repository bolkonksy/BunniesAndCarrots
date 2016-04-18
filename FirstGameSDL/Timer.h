#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer {
public:
	Timer();

	Uint32 getTime();

private:
	Uint32 _startTime;
};


#endif