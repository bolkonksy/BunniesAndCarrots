#include "Carrot.h"

#include "Random.h"

void Carrot::init(Game* game, ResourceManager* rm, int id, float spawnX, float spawnY)
{
	_game = game;
	_rm = rm;

	_border_x1 = CFG::GAME_BORDER_X1;
	_border_x2 = CFG::GAME_BORDER_X2;
	_border_y1 = CFG::GAME_BORDER_Y1;
	_border_y2 = CFG::GAME_BORDER_Y2;
	
	_sizeX = 20;
	_sizeY = 20;

	_carrotFrame = 0.0f;
	relocate();

	_texture = rm->getTexture("Textures/mrkva.png");
}

void Carrot::update(float deltaTime)
{
	_carrotFrame += (deltaTime + Random::randNumber(10, 500) / 10000.0f) / 8;

	if (_carrotFrame >= 2.0f)
		_carrotFrame = 0.0f;

	_destRect.x = (int)_x;
	_destRect.y = (int)_y;
	_destRect.w = (int)_sizeX;
	_destRect.h = (int)_sizeY;

	/* If carrot stops blinking or any other similar problem appears,
	   play around with the second line - cast operators probably */
	_srcRect.x = 0;
	_srcRect.y = (int)_carrotFrame * (int)_sizeY;
	_srcRect.w = (int)_sizeX;
	_srcRect.h = (int)_sizeY;
}

void Carrot::render()
{
	SDL_RenderCopy(_game->getRenderer(), _texture, &_srcRect, &_destRect);
}

void Carrot::relocate()
{
	/* +4 and -4 is here so this object wouldn't spawn right next to the game border */
	_x = Random::randNumber(_border_x1 + 4.0f, _border_x2 - _sizeX - 4.0f);
	_y = Random::randNumber(_border_y1 + 4.0f, _border_y2 - _sizeY - 4.0f);

	_carrotFrame = (float)Random::randNumber(0, 1);
}
