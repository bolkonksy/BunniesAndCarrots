#ifndef STATE_END_H
#define STATE_END_H

#include "GameState.h"
#include "Configuration.h"
#include "Stats.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Font.h"
#include "Player.h"

class State_End : public GameState {
private:
	ResourceManager* _rm;

	Font* _font;

	/* These variables are the same as in stats.h */
	unsigned int _P1_score;
	unsigned int _P2_score;

	unsigned int _P1_victories;
	unsigned int _P2_victories;

	Uint32 _gameplayTime;
	EndMode _stateGameplayEnd;


public:
	bool Init(Game* game);
	void HandleEvents(SDL_Event* event);
	void Update(float deltaTime);
	void Render();
	void Quit();


	/* Unnecessary for this state - inherited functions */
	bool isColliding(Object* thisObject, Object* other);
	Player* getPlayer(int playerIndex);
	void setEndMode(int winner, EndMode endMode);
};

#endif