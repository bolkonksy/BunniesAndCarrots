#include "Player.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "GameState.h"


Player::~Player()
{
	delete _font;
	_font = NULL;
}
void Player::init(Game* game, ResourceManager* rm, int id, float spawnX, float spawnY)
{
	_game = game;
	_rm = rm;
	_id = id;

	_border_x1 = CFG::GAME_BORDER_X1;
	_border_x2 = CFG::GAME_BORDER_X2;
	_border_y1 = CFG::GAME_BORDER_Y1;
	_border_y2 = CFG::GAME_BORDER_Y2;

	_font = new Font(_game, _rm->getTexture("Textures/font_texture.png"), 16, 16, 8, 16);

	_sizeX = CFG::PLAYER_SIZE_X;
	_sizeY = CFG::PLAYER_SIZE_Y;

	_x = spawnX; /* Center: (game->getWidth() - _sizeX) / 2 */
	_y = spawnY; /* Center: (game->getHeight() - _sizeY )/ 2 */

	_sheetRow = 0.0f;
	_sheetCol = 0.0f;
	_animSpeed = 12.0f;
	_sheet = rm->getTexture("Textures/bunnies.png");
	setColor();

	_moveSpeed = CFG::START_SPEED;

	_dirX = 0.0f;
	_dirY = 0.0f;

	_invertedContorlsTime = 0;

	_poisonTime = CFG::POISON_TIME;
	_mad = false;
	_score = 0;
}
void Player::update(float deltaTime)
{
	if (_invertedContorlsTime > _timer.getTime()) {
		_dirX *= -1;
		_dirY *= -1;
	}

	if (_dirX != 0.0f || _dirY != 0.0f) {
		_sheetRow += _animSpeed * deltaTime;
		if (_sheetRow >= 4) {
			_sheetRow = 0.0f;
		}
	} else {
		_sheetRow = 0.0f;
	}

	if (_dirX > 0)
		_sheetCol = 3;
	if (_dirX < 0)
		_sheetCol = 2;
	if (_dirY > 0)
		_sheetCol = 0;
	if (_dirY < 0)
		_sheetCol = 1;

	//_moveSpeed += (float)_score * 0.01f; LOL, ovo je bia fail koji je dosta dugo osta neprimjecen
	//lol failer noob

	/* Updating position */
	_x += _dirX * deltaTime * _moveSpeed;
	_y += _dirY * deltaTime * _moveSpeed;
	
	if (playersCollision(_id)) {
		if (isMad()) 
			_game->getState()->setEndMode(_id, EndMode::GOT_EATEN_MODE);
		else {
		_x -= _dirX * deltaTime * _moveSpeed;
		_y -= _dirY * deltaTime * _moveSpeed;
		}
	}

	if (_x > _border_x2 - _sizeX)
		_x = _border_x2 - _sizeX;
	if (_x < _border_x1)
		_x = _border_x1;
	if (_y > _border_y2 - _sizeY)
		_y = _border_y2 - _sizeY;
	if (_y < _border_y1)
		_y = _border_y1;

	/* I could put the last two (.w and .h) in the init function, but idc */
	_srcRect.x = (int)_sizeX * (int)_sheetCol;
	_srcRect.y = (int)_sizeY * (int)_sheetRow;
	_srcRect.w = (int)_sizeX;
	_srcRect.h = (int)_sizeY;

	/* I could put the last two (.w and .h) in the init function, but idc */
	_destRect.x = (int)_x;
	_destRect.y = (int)_y;
	_destRect.w = (int)_sizeX;
	_destRect.h = (int)_sizeY;

	/* These two should be reseted every update */
	_dirX = 0.0f;
	_dirY = 0.0f;

	if (isMad()) {
		/* Int cast is here, because a negative Uint32(Unsigned int) 
		 * value is actually a huge number UINT32_MAX - some value */
		if ((int)_poisonTime < (int)_timer.getTime() - (int)_startPoisonTime) {

			/* If player one has lost, then player two has won */
			if (_id == 1)
				_game->getState()->setEndMode(2, EndMode::POISONED_MODE);

			/* If player two has lost, then player one has won */
			else
				_game->getState()->setEndMode(1, EndMode::POISONED_MODE);
		}
	}
}
void Player::render()
{
	setColor();	
	/* Rendering a player number above the player */
	/* -8 and -16 in position argument is actually a texture size of each letter */
	_font->renderChar((int)(_x + _sizeX / 2 - 8 / 2), (int)(_y - _sizeY / 4 - 16 / 2), _id + '0');

	/* If player is mad, this will display timeleft countdown */
	if (isMad()) {
		_timeLeft = (int)_poisonTime - ((int)_timer.getTime() - (int)_startPoisonTime);

		_font->setColor(CFG::BLACK_COLOR.r, CFG::BLACK_COLOR.g, CFG::BLACK_COLOR.b);
		std::stringstream timeLeft;
		timeLeft << std::setw(3) << std::setfill(' ') << _timeLeft / 1000 << "."
			<< std::setw(2) << std::setfill('0') << (_timeLeft % 1000) / 10; /* For decimals */
		_font->renderString((_game->getWidth() - 50) - 137, 5, timeLeft.str());

		timeLeft.str(std::string()); /* Emptying the string stream for the next use */
	}

	SDL_RenderCopy(_game->getRenderer(), _sheet, &_srcRect, &_destRect);
}
void Player::move(int dX, int dY)
{
	if (dX && dY)
	{
		_dirX += (float)dX / 1.41421356237f;
		_dirY += (float)dY / 1.41421356237f;
	}
	else
	{
		_dirX += (float)dX;
		_dirY += (float)dY;
	}
}
void Player::setScore(unsigned int score)
{
	if (score == -1)
		_score = 0;
	else
		_score += score;
}
void Player::setMadMode(bool value)
{
	_startPoisonTime = _timer.getTime();
	_mad = value;
}
void Player::incrementSpeed()
{
	if (_moveSpeed >= CFG::START_SPEED * 8) {
		_moveSpeed += CFG::SPEED_INCREASE / 8;
	} else if (_moveSpeed >= CFG::START_SPEED * 4) {
		_moveSpeed += CFG::SPEED_INCREASE / 4;
	} else if (_moveSpeed >= CFG::START_SPEED * 2) {
		_moveSpeed += CFG::SPEED_INCREASE / 2;
	} else {
		_moveSpeed += CFG::SPEED_INCREASE / 1;
	}
}
void Player::decrementSpeed(float minusSpeed, float scale)
{
	if (_moveSpeed < 32.0f) {
		_moveSpeed -= minusSpeed * scale / 4.0f;
	} else if (_moveSpeed < 48.0f) {
		_moveSpeed -= minusSpeed * scale / 2.0f;
	} else {
		_moveSpeed -= minusSpeed * scale;
	}
}
void Player::increasePoisonTime(Uint32 plusTime)
{
	_startPoisonTime += plusTime;
}
void Player::setInvertedControls(Uint32 time)
{
	_invertedContorlsTime = _timer.getTime() + time;
}

unsigned int Player::getScore()
{
	return _score;
}
float Player::getSpeed()
{
	return _moveSpeed;
}
bool Player::isMad()
{
	return _mad;
}
void Player::setColor()
{
	if (_id == 1) {
		SDL_SetTextureColorMod(_sheet, CFG::PLAYER_1.r, CFG::PLAYER_1.g, CFG::PLAYER_1.b);
		_font->setColor(CFG::PLAYER_FONT_1.r, CFG::PLAYER_FONT_1.g, CFG::PLAYER_FONT_1.b);
	} else if (_id == 2) {
		SDL_SetTextureColorMod(_sheet, CFG::PLAYER_2.r, CFG::PLAYER_2.g, CFG::PLAYER_2.b);
		_font->setColor(CFG::PLAYER_FONT_2.r, CFG::PLAYER_FONT_2.g, CFG::PLAYER_FONT_2.b);
	} else {
		SDL_SetTextureColorMod(_sheet, 0, 0, 0);
		_font->resetColor();
	}

	if (isMad()) {
		if (_id == 2) {
			if (9 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_2.r * 1 / 18, CFG::PLAYER_2.g * 1 / 18, CFG::PLAYER_2.b * 1 / 18);
			else if (8 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_2.r * 3 / 18, CFG::PLAYER_2.g * 3 / 18, CFG::PLAYER_2.b * 3 / 18);
			else if (7 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_2.r * 5 / 18, CFG::PLAYER_2.g * 5 / 18, CFG::PLAYER_2.b * 5 / 18);
			else if (6 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_2.r * 7 / 18, CFG::PLAYER_2.g * 7 / 18, CFG::PLAYER_2.b * 7 / 18);
			else if (5 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_2.r * 9 / 18, CFG::PLAYER_2.g * 9 / 18, CFG::PLAYER_2.b * 9 / 18);
			else if (4 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_2.r * 11 / 18, CFG::PLAYER_2.g * 11 / 18, CFG::PLAYER_2.b * 11 / 18);
			else if (3 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_2.r * 13 / 18, CFG::PLAYER_2.g * 13 / 18, CFG::PLAYER_2.b * 13 / 18);
			else if (2 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_2.r * 14 / 18, CFG::PLAYER_2.g * 14 / 18, CFG::PLAYER_2.b * 14 / 18);
			else if (1 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_2.r * 16 / 18, CFG::PLAYER_2.g * 16 / 18, CFG::PLAYER_2.b * 16 / 18);
			else
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_2.r * 17 / 18, CFG::PLAYER_2.g * 17 / 18, CFG::PLAYER_2.b * 17 / 18);
		} else {
			if (9 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_1.r * 1 / 18, CFG::PLAYER_1.g * 1 / 18, CFG::PLAYER_1.b * 1 / 18);
			else if (8 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_1.r * 3 / 18, CFG::PLAYER_1.g * 3 / 18, CFG::PLAYER_1.b * 3 / 18);
			else if (7 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_1.r * 5 / 18, CFG::PLAYER_1.g * 5 / 18, CFG::PLAYER_1.b * 5 / 18);
			else if (6 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_1.r * 7 / 18, CFG::PLAYER_1.g * 7 / 18, CFG::PLAYER_1.b * 7 / 18);
			else if (5 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_1.r * 9 / 18, CFG::PLAYER_1.g * 9 / 18, CFG::PLAYER_1.b * 9 / 18);
			else if (4 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_1.r * 11 / 18, CFG::PLAYER_1.g * 11 / 18, CFG::PLAYER_1.b * 11 / 18);
			else if (3 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_1.r * 13 / 18, CFG::PLAYER_1.g * 13 / 18, CFG::PLAYER_1.b * 13 / 18);
			else if (2 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_1.r * 14 / 18, CFG::PLAYER_1.g * 14 / 18, CFG::PLAYER_1.b * 14 / 18);
			else if (1 * (int)_poisonTime / 10 < (int)_timer.getTime() - (int)_startPoisonTime)
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_1.r * 16 / 18, CFG::PLAYER_1.g * 16 / 18, CFG::PLAYER_1.b * 16 / 18);
			else
				SDL_SetTextureColorMod(_sheet, CFG::PLAYER_1.r * 17 / 18, CFG::PLAYER_1.g * 17 / 18, CFG::PLAYER_1.b * 17 / 18);
		}
	}
}
bool Player::playersCollision(int id)
{
	Player* otherPlayer = _game->getState()->getPlayer(id);
	if (_game->getState()->isColliding(this, otherPlayer))
		return true;

	return false;
}

