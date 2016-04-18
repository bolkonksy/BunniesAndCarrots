#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL.h>
#include "Game.h"
#include "Object.h"
#include "Player.h"
#include "Stats.h"

class GameState {
protected:
	Game* _game;

public:
	/* Basic functions */
	virtual bool Init(Game* game) = 0;
	virtual void HandleEvents(SDL_Event* event) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Quit() = 0;

	/* State_Gameplay functions */
	virtual bool isColliding(Object* thisObject, Object* other) { return false; };
	virtual Player* getPlayer(int playerIndex) = 0;
	virtual void setEndMode(int winner, EndMode endMode) = 0;
};


#endif