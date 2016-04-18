#ifndef STATS_H
#define STATS_H

#include <SDL.h>

enum class EndMode { PLAY_MODE, NORMAL_END, GOT_EATEN_MODE, POISONED_MODE, NOT_STARTED, FINISHED };

class Stats {
private:
	unsigned int _P1_score;
	unsigned int _P2_score;

	unsigned int _P1_victories;
	unsigned int _P2_victories;

	Uint32 _gameplayTime;
	EndMode _stateGameplayEnd;

public:
	Stats();

	/* Setters */
	void SetP1Score(unsigned int score = 0);
	void SetP2Score(unsigned int score = 0);
	void P1AddVictory(); /* Just adds one victory */
	void P2AddVictory(); /* Just adds one victory */
	void SetGameplayTime(Uint32 time = 0);
	void SetStateGameplayEnd(EndMode mode);

	/* Getters */
	unsigned int GetP1Score();
	unsigned int GetP2Score();
	unsigned int GetP1Victories();
	unsigned int GetP2Victories();
	Uint32 GetGameplayTime();
	EndMode GetStateGameplayEnd();
};


#endif