#ifndef PLAYER_H
#define PLAYER_H

#include "Configuration.h"
#include "Object.h"
#include "Font.h"
#include "Timer.h"


class Player : public Object {
private:
	SDL_Texture* _sheet;

	/* If there are more players */
	int _playerIndex;

	/* Each player has its own score variable */
	unsigned int _score;

	/* Player speed [pixel/second] */
	float _moveSpeed;
	
	/* For animating player */
	float _sheetRow;
	float _sheetCol;
	/* For incrementing sheetRow */
	float _animSpeed;

	/* Facing direction of the player */
	float _dirX, _dirY;

	/* For mad mode when player eats mad flower */
	bool _mad;
	Uint32 _poisonTime;
	Uint32 _startPoisonTime;
	int _timeLeft;

	Uint32 _invertedContorlsTime;
	
	Timer _timer;

	/* For printing PlayerNumber above player */
	Font* _font;

public:
	~Player();

	void init(Game* game, ResourceManager* rm, int id, float spawnX = 400.0f, float spawnY = 300.0f);
	void update(float deltaTime);
	void render();

	/* Setters */
	void move(int dX, int dY);
	void setScore(unsigned int score);
	void setMadMode(bool value);
	void incrementSpeed();
	void decrementSpeed(float minusSpeed, float scale = 1.0f);
	void increasePoisonTime(Uint32 plusTime);
	void setInvertedControls(Uint32 time);

	/* Getters */
	unsigned int getScore();
	float getSpeed();
	bool isMad();

private:
	/* This can be only set in the source code. sorries */
	void setColor();
	bool playersCollision(int id);
};

#endif