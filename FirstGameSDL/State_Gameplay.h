#ifndef STATE_GAMEPLAY_H
#define STATE_GAMEPLAY_H

#include <vector>

#include "Configuration.h"
#include "GameState.h"
#include "State_End.h"
#include "Stats.h"
#include "ResourceManager.h"
#include "Level.h"
#include "Font.h"
#include "Timer.h"
#include "Player.h"
#include "Carrot.h"
#include "Flower_Dead.h"
#include "Flower_Slow.h"
#include "Flower_Mad.h"
#include "Flower_Inverted.h"
#include "Flower_Speed.h"


class State_Gameplay : public GameState {
private:
	ResourceManager* _rm;

	std::vector<Carrot*> _carrots;
	std::vector<Flower_Dead*> _flowers_dead;
	std::vector<Flower_Slow*> _flowers_slow;
	std::vector<Flower_Mad*> _flowers_mad;
	std::vector<Flower_Inverted*> _flowers_inverted;
	std::vector<Flower_Speed*> _flowers_speed;

	Player Player1;
	Player Player2;
	int _winner;
	EndMode _endMode;

	Level* _level;
	Font* _font;
	Timer* _timer;

public:
	bool Init(Game* game);
	void HandleEvents(SDL_Event* event);
	void Update(float deltaTime);
	void Render();
	void Quit();

	/* Collision between two objects */
	bool isColliding(Object* thisObject, Object* other);

	/* To get both players in Player class for checking collision.
	 * And to get winner in the EndState */
	Player* getPlayer(int playerIndex);

	/* Sets ending mode, winner and adds one victory to winner */
	void setEndMode(int winner, EndMode endMode);

	/* Used for checking if a spawn location is available */
	/* It checks collision with every object on the map */
	bool collideWithOtherObjects(Object* object);

private:
	/* If the game is ended in proper way. This functions also
	* calls Pop() for this state and Push() for the next state */
	void theEnd(); /* Only for this gamestate */

};

#endif