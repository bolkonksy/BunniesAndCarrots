#ifndef FONT_H
#define FONT_H

#include <string>
#include "Game.h"


class Font {
private:
	SDL_Texture* _sheet;

	int _charWidth;
	int _charHeight;

	int _numCharsX;
	int _numCharsY;

	Game* _game;

public:
	Font(Game* game, SDL_Texture* sheet, int numCharsX, int numCharsY, int charWidth, int charHeight);
	
	void renderChar(int x, int y, unsigned char data, int fontSize = 1);
	void renderString(int x, int y, std::string data, int fontSize = 1);

	void setColor(Uint8 red, Uint8 blue, Uint8 green);
	void resetColor();
};


#endif