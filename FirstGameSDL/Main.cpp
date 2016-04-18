#include "Game.h"
#include "State_Gameplay.h"
#include "State_Menu.h"

int main(int argc, char *argv[])
{
	Game game;

	if (game.init(new State_Menu()))
		game.thread();

	return 0;	
}