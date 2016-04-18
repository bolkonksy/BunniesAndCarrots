#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <SDL.h>


namespace CFG {

	/* Window Settings */
	static int SCREEN_WIDTH = 800; // Default: 800
	static int SCREEN_HEIGHT = 600; // Default: 600
	static bool SHOW_CURSOR = SDL_DISABLE; // Default: SDL_ENABLE

	/* Game Settings */
	static float GAME_BORDER_X1 = 21.0f; // Default: 21.0f
	static float GAME_BORDER_X2 = 776.0f; // Default: 776.0f
	static float GAME_BORDER_Y1 = 46.0f; // Default: 46.0f
	static float GAME_BORDER_Y2 = 579.0f; // Default: 579.0f

	/* Number of Objects */
	static unsigned int MAX_CARROTS = 20; // Default: 40
	static unsigned int MAX_FLOWERS_DEAD = 12; // Default: 15
	static unsigned int MAX_FLOWERS_SLOW = 4; // Default: 3
	static unsigned int MAX_FLOWERS_MAD = 1; // Default: 15
	static unsigned int MAX_FLOWERS_INVERTED = 1; // Default: 1
	static unsigned int MAX_FLOWERS_SPEED = 2; // Default: 4

	/* Object Properties */
	static float FLOWER01_SIZE_X = 10.0f; // Default: 15.0f
	static float FLOWER01_SIZE_Y = 18.0f; // Default: 25.0f
	static float FLOWER02_SIZE_X = 19.0f; // Default: 19.0f
	static float FLOWER02_SIZE_Y = 32.0f; // Default: 32.0f

	/* Player Settings */
	static float P1_SPAWN_POS_X = (SCREEN_WIDTH / 3.0f);  // Default: SCREEN_WIDTH / 3.0f
	static float P1_SPAWN_POS_Y = (SCREEN_HEIGHT / 2.0f); // Default: SCREEN_HEIGHT / 2.0f
	static float P2_SPAWN_POS_X = (SCREEN_WIDTH / 3 * 2.0f); // Default: SCREEN_WIDTH / 3 * 2.0f
	static float P2_SPAWN_POS_Y = (SCREEN_HEIGHT / 2.0f); // Default: SCREEN_HEIGHT / 2.0f
	static float PLAYER_SIZE_X = 45.0f; // Default: 16.0f
	static float PLAYER_SIZE_Y = 37.0f; // Default: 32.0f
	static float START_SPEED = 64.0f; // Default: 64.0f
	static float SPEED_INCREASE = 16.0f; // Default: 12.0f
	static float SPEED_DECREASE = 20.0f; // Default: 20.0f
	static Uint32 POISON_TIME = 10 * 1000; // Default: 10 * 1000 <-- it's in miliseconds
	static Uint32 POISON_TIME_INCREASE = 3 * 1000; // Default: 2 * 1000 <-- it's in miliseconds
	static Uint32 INVERTED_CONTROLS_TIME = 4 * 1000; // Default: 4 * 1000 <-- it's in miliseconds


	/* Font and Color Settings*/
	static SDL_Color PLAYER_1 = { 127, 127, 255, 255 }; // Default: { 127, 127, 255, 255 }
	static SDL_Color PLAYER_2 = { 255, 127, 127, 255 }; // Default: { 255, 127, 127, 255 }
	static SDL_Color PLAYER_FONT_1 = { 12, 255, 255, 255 }; // Default: { 31, 255, 255, 255 }
	static SDL_Color PLAYER_FONT_2 = { 255, 44, 44, 255 }; // Default: { 255, 63, 63, 255 }
	static SDL_Color MAP_COLOR = { 235, 235, 235, 255 }; // Normal color: { 255, 255, 255, 255 }
	static SDL_Color WHITE_COLOR = { 255, 255, 255, 255 };
	static SDL_Color BLACK_COLOR = { 0, 0, 0, 255 };


	/* To do:
		sounds and music
		add healing flower?

		rotation of flowers and carrots
		create window class and separate it from game init
		put using CFG::PLAYERCOLOR almost everywhere
		scoring in the last gamestate
		mybe playagain option in the endstate
	*/

	/* To fix:
		fix dead flower distance from the border
	*/
}

#endif // !CONFIGURATION_H
