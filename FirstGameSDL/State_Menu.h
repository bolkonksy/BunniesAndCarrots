#ifndef STATE_MENU_H
#define STATE_MENU_H

#include "Object.h"
#include "State_Gameplay.h"
#include "GameState.h"
#include "ResourceManager.h"
#include "Font.h"
#include "Player.h"

class State_Menu : public GameState {
private:
	ResourceManager* _rm;

	Font* _font;
	float _blinking;

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