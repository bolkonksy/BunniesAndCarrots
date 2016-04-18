#include "Font.h"


Font::Font(Game* game, SDL_Texture* sheet, int numCharsX, int numCharsY, int charWidth, int charHeight)
{
	_game = game;
	_sheet = sheet;
	_numCharsX = numCharsX;
	_numCharsY = numCharsY;
	_charWidth = charWidth;
	_charHeight = charHeight;
}

void Font::renderChar(int x, int y, unsigned char data, int fontSize)
{
	SDL_Rect srcRect, destRect;

	srcRect.x = (data % _numCharsX) * _charWidth;
	srcRect.y = (data / _numCharsX) * _charHeight;;
	srcRect.w = _charWidth;
	srcRect.h = _charHeight;

	destRect.x = x;
	destRect.y = y;
	destRect.w = _charWidth * fontSize;
	destRect.h = _charHeight * fontSize;

	SDL_RenderCopy(_game->getRenderer(), _sheet, &srcRect, &destRect);
}

void Font::renderString(int x, int y, std::string data, int fontSize)
{
	for (std::string::size_type i = 0; i < data.length(); i++) {
		renderChar(x + (int)i * _charWidth * fontSize, y, data.at(i), fontSize);
	}
}

void Font::setColor(Uint8 red, Uint8 blue, Uint8 green)
{
	SDL_SetTextureColorMod(_sheet, red, blue, green);
}

void Font::resetColor()
{
	SDL_SetTextureColorMod(_sheet, 255, 255, 255);
}
