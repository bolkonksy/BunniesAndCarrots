#include "State_End.h"

#include <sstream>
#include <ios>

using CFG::PLAYER_1;
using CFG::PLAYER_FONT_2;
using CFG::BLACK_COLOR;

bool State_End::Init(Game* game)
{
	_game = game;

	_rm = new ResourceManager(game);

	try {
		_rm->loadTexture("Textures/font_texture.png");
	}
	catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
		return false;
	}

	_font = new Font(_game, _rm->getTexture("Textures/font_texture.png"), 16, 16, 8, 16);

	/* Getting stats */
	_P1_score = _game->getStats()->GetP1Score();
	_P2_score = _game->getStats()->GetP2Score();
	_P1_victories = _game->getStats()->GetP1Victories();
	_P2_victories = _game->getStats()->GetP2Victories();
	_gameplayTime = _game->getStats()->GetGameplayTime();
	_stateGameplayEnd = _game->getStats()->GetStateGameplayEnd();

	return true;
}
void State_End::HandleEvents(SDL_Event* event)
{
	if (event->type == SDL_QUIT)
		_game->setQuit();
	else if (event->type == SDL_KEYDOWN) {

		if (event->key.keysym.sym == SDLK_ESCAPE)
			_game->popState();

		if (event->key.keysym.sym == SDLK_RETURN)
			_game->popState();
	}
	
}
void State_End::Update(float deltaTime)
{
	if (_P1_victories > _P2_victories)
		SDL_SetRenderDrawColor(_game->getRenderer(), PLAYER_1.r, PLAYER_1.g, PLAYER_1.b, PLAYER_1.a);
	else if (_P2_victories > _P1_victories)
		SDL_SetRenderDrawColor(_game->getRenderer(), PLAYER_FONT_2.r, PLAYER_FONT_2.g, PLAYER_FONT_2.b, PLAYER_FONT_2.a);
	else
		SDL_SetRenderDrawColor(_game->getRenderer(), BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, BLACK_COLOR.a);
}
void State_End::Render()
{
	std::stringstream text("PRESS ENTER FOR MAIN MENU");

	std::streamsize x = text.str().length() * 8 / 2;
	_font->renderString(_game->getWidth() / 2 - 3 * (int)x, _game->getHeight() / 3, text.str(), 3);
	text.str("");

	text << "P1 VICTORIES: " << _P1_victories;
	x = text.str().length() * 8 / 2;
	_font->renderString( _game->getWidth() / 4 - 2 * (int)x, _game->getHeight() / 2, text.str(), 2);
	text.str("");

	text << "P2 VICTORIES: " << _P2_victories;
	x = text.str().length() * 8 / 2;
	_font->renderString(_game->getWidth() / 4 * 3- 2 * (int)x, _game->getHeight() / 2, text.str(), 2);
	text.str("");

}
void State_End::Quit()
{
	delete _font;
	_font = NULL;
	delete _rm;
	_rm = NULL;
}


/* Unnecessary for this state - inherited functions */
bool State_End::isColliding(Object* thisObject, Object* other)
{
	return false;
}
Player* State_End::getPlayer(int playerIndex)
{
	return NULL;
}
void State_End::setEndMode(int winner, EndMode endMode)
{
}
