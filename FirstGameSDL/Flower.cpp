#include "Flower.h"

#include "Random.h"
#include "ResourceManager.h"


void Flower::render()
{
	/* Using NULL here for destRect automatically takes the whole texture */
	SDL_RenderCopy(_game->getRenderer(), _texture, NULL, &_destRect);
}

void Flower::update(float deltaTime)
{
	/* Only these two are important for rendering flowers */
	_destRect.x = (int)_x;
	_destRect.y = (int)_y;
}

void Flower::spawn(bool noRespawn)
{
	if (noRespawn) {
		/* Coordinates outside of the window border */
		_x = _game->getWidth() - 30.0f;
		_y = _game->getWidth() - 30.0f;
	} else {
		/* +4 and -4 is here so this object wouldn't spawn right next to the game border */
		_x = Random::randNumber(_border_x1 + 4.0f, _border_x2 - _sizeX - 4.0f);
		_y = Random::randNumber(_border_y1 + 4.0f, _border_y2 - _sizeY - 4.0f);
	}
}
