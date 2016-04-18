#include "Timer.h"


Timer::Timer()
{
	_startTime = SDL_GetTicks();
}

Uint32 Timer::getTime()
{
	return SDL_GetTicks() - _startTime;
}
