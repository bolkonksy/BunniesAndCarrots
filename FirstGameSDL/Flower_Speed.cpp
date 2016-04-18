#include "Flower_Speed.h"


void Flower_Speed::init(Game* game, ResourceManager* rm, int id, float spawnX, float spawnY)
{
	_game = game;
	_rm = rm;

	_border_x1 = CFG::GAME_BORDER_X1;
	_border_x2 = CFG::GAME_BORDER_X2;
	_border_y1 = CFG::GAME_BORDER_Y1;
	_border_y2 = CFG::GAME_BORDER_Y2;

	_sizeX = CFG::FLOWER02_SIZE_X;
	_sizeY = CFG::FLOWER02_SIZE_Y;

	spawn();

	_destRect.x = (int)_x;
	_destRect.y = (int)_y;
	_destRect.w = (int)_sizeX * 5 / 6;
	_destRect.h = (int)_sizeY * 5 / 6;

	_texture = _rm->getTexture("Textures/flower05.png");
}