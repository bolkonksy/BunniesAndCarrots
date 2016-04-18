#include "Stats.h"

Stats::Stats()
{
	_P1_score = 0;
	_P2_score = 0;

	_P1_victories = 0;
	_P2_victories = 0;

	_gameplayTime = 0;
	_stateGameplayEnd = EndMode::NOT_STARTED;
}

/* Setters */
void Stats::SetP1Score(unsigned int score)
{
	_P1_score = score;
}
void Stats::SetP2Score(unsigned int score)
{
	_P2_score = score;
}
void Stats::P1AddVictory()
{
	_P1_victories++;
}
void Stats::P2AddVictory()
{
	_P2_victories++;
}
void Stats::SetGameplayTime(Uint32 time)
{
	_gameplayTime = time;
}
void Stats::SetStateGameplayEnd(EndMode mode)
{
	_stateGameplayEnd = mode;
}

/* Getters */
unsigned int Stats::GetP1Score()
{
	return _P1_score;
}
unsigned int Stats::GetP2Score()
{
	return _P2_score;
}
unsigned int Stats::GetP1Victories()
{
	return _P1_victories;
}
unsigned int Stats::GetP2Victories()
{
	return _P2_victories;
}
Uint32 Stats::GetGameplayTime()
{
	return _gameplayTime;
}
EndMode Stats::GetStateGameplayEnd()
{
	return _stateGameplayEnd;
}

