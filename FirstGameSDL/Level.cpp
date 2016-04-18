#include "Level.h"

#include <iomanip> // Manipulators: for setw() and setfill()

Level::Level(Game* game, ResourceManager* rm, Timer* timer)
{
	_game = game;
	_rm = rm;
	_timer = timer;
	_map = NULL;
}

Level::~Level()
{
	delete _font;
	_font = NULL;

	_map = NULL;

}

void Level::init()
{
	_map = _rm->getTexture("Textures/map.png");
	SDL_SetTextureColorMod(_map, CFG::MAP_COLOR.r, CFG::MAP_COLOR.g, CFG::MAP_COLOR.b);
	_font = new Font(_game, _rm->getTexture("Textures/font_texture.png"), 16, 16, 8, 16);

	_P1text = "P1 > Score:    - Speed:";
	_P2text = "P2 > Score:    - Speed:";
	_textTime = "Time:";
	_lifeLeft = "Life Left:";
}

void Level::render()
{
	/* Rendering map on the screen */
	SDL_Rect screen = { 0, 0, _game->getWidth(), _game->getHeight() };
	SDL_RenderCopy(_game->getRenderer(), _map, NULL, &screen);

	/* Rendering text: player1 score and speed */
	_font->setColor(CFG::PLAYER_FONT_1.r, CFG::PLAYER_FONT_1.g, CFG::PLAYER_FONT_1.b);
	_font->renderString(7, 5, _P1text);

	/* Rendering text: player2 score and speed */
	_font->setColor(CFG::PLAYER_FONT_2.r, CFG::PLAYER_FONT_2.g, CFG::PLAYER_FONT_2.b);
	_font->renderString((_game->getWidth() / 2) + 7 - 135, 5, _P2text);

	/* Rendering text: time counter and life left */
	_font->setColor(CFG::BLACK_COLOR.r, CFG::BLACK_COLOR.g, CFG::BLACK_COLOR.b);
	_font->renderString((_game->getWidth() - 100 - 2), 5, _textTime);
	_font->renderString((_game->getWidth() - 100) - 160, 5, _lifeLeft);

	/* Rendering calculated time in seconds converted to text in this format: 000.00  */
	_gameplayTime << std::setw(3) << std::setfill(' ') << (int)_timer->getTime() / 1000 << "."
		<< std::setw(2) << std::setfill('0') << ((int)_timer->getTime() % 1000) / 10; /* For decimals */
	_font->renderString((_game->getWidth() - 100) + 40, 5, _gameplayTime.str());

	_gameplayTime.str(std::string()); /* Emptying the string stream for the next use */
}

/* STARI KVADRAT U RENDER FJ-I!!! MOZDA OPET ZATREBA, JEDNOM
SDL_SetRenderDrawColor(_game->getRenderer(), 0xB, 0xB0, 0x30, 0xFF);
SDL_RenderClear(_game->getRenderer());

SDL_SetRenderDrawColor(_game->getRenderer(), 0x00, 0x00, 0x00, 0xFF);
SDL_Rect d = { 28, 28, _game->getWidth() - 2*28, _game->getHeight() - 2*28 };
SDL_RenderDrawRect(_game->getRenderer(), &d);*/
