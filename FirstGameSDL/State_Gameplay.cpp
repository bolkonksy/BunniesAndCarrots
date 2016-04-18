#include "State_Gameplay.h"

#include "Random.h"

bool State_Gameplay::Init(Game* game)
{
	_game = game;
	_endMode = EndMode::PLAY_MODE;

	/* Stats reset */
	_game->getStats()->SetP1Score();
	_game->getStats()->SetP2Score();
	_game->getStats()->SetGameplayTime();
	_game->getStats()->SetStateGameplayEnd(EndMode::PLAY_MODE);

	_rm = new ResourceManager(game);
	try {
		_rm->loadTexture("Textures/bunnies.png");
		_rm->loadTexture("Textures/font_texture.png");
		_rm->loadTexture("Textures/map.png");
		_rm->loadTexture("Textures/flower01.png"); 
		_rm->loadTexture("Textures/flower02.png");
		_rm->loadTexture("Textures/flower03.png");
		_rm->loadTexture("Textures/flower04.png");
		_rm->loadTexture("Textures/flower05.png");
		_rm->loadTexture("Textures/mrkva.png");
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
		return false;
	}

	_font = new Font(_game, _rm->getTexture("Textures/font_texture.png"), 16, 16, 8, 16);
	_timer = new Timer();
	_level = new Level(_game, _rm, _timer);
	_level->init();

	Player1.init(_game, _rm, 1, CFG::P1_SPAWN_POS_X, CFG::P1_SPAWN_POS_Y);
	Player2.init(_game, _rm, 2, CFG::P2_SPAWN_POS_X, CFG::P2_SPAWN_POS_Y);

	for (unsigned int i = 0; i < CFG::MAX_FLOWERS_DEAD; i++) {
		_flowers_dead.push_back(new Flower_Dead());
		_flowers_dead.back()->init(_game, _rm);

		while (collideWithOtherObjects(_flowers_dead.back())) {
			_flowers_dead.back()->spawn();
		}
	}
	for (unsigned int i = 0; i < CFG::MAX_CARROTS; i++) {
		_carrots.push_back(new Carrot());
		_carrots.back()->init(_game, _rm);

		while (collideWithOtherObjects(_carrots.back())) {
			_carrots.back()->relocate();
		}
	}
	for (unsigned int i = 0; i < CFG::MAX_FLOWERS_SLOW; i++) {
		_flowers_slow.push_back(new Flower_Slow());
		_flowers_slow.back()->init(_game, _rm);

		while (collideWithOtherObjects(_flowers_slow.back())) {
			_flowers_slow.back()->spawn();
		}
	}
	for (unsigned int i = 0; i < CFG::MAX_FLOWERS_MAD; i++) {
		_flowers_mad.push_back(new Flower_Mad());
		_flowers_mad.back()->init(_game, _rm);

		while (collideWithOtherObjects(_flowers_mad.back())) {
			_flowers_mad.back()->spawn();
		}
	}
	for (unsigned int i = 0; i < CFG::MAX_FLOWERS_INVERTED; i++) {
		_flowers_inverted.push_back(new Flower_Inverted());
		_flowers_inverted.back()->init(_game, _rm);

		while (collideWithOtherObjects(_flowers_inverted.back())) {
			_flowers_inverted.back()->spawn();
		}
	}
	for (unsigned int i = 0; i < CFG::MAX_FLOWERS_SPEED; i++) {
		_flowers_speed.push_back(new Flower_Speed());
		_flowers_speed.back()->init(_game, _rm);

		while (collideWithOtherObjects(_flowers_speed.back())) {
			_flowers_speed.back()->spawn();
		}
	}
	return true;
}
void State_Gameplay::HandleEvents(SDL_Event* event)
{
	if (event->type == SDL_QUIT)
		_game->setQuit();
	else if (event->type == SDL_KEYDOWN) {
		if (event->key.keysym.sym == SDLK_ESCAPE)
			_game->popState();
	}
}
void State_Gameplay::Update(float deltaTime)
{
	if (_endMode == EndMode::FINISHED) {
		_game->popState();

	} else {
		const Uint8* keyboard = SDL_GetKeyboardState(NULL);

		if (keyboard[SDL_SCANCODE_UP])
			Player1.move(0, -1);
		if (keyboard[SDL_SCANCODE_DOWN])
			Player1.move(0, 1);
		if (keyboard[SDL_SCANCODE_LEFT])
			Player1.move(-1, 0);
		if (keyboard[SDL_SCANCODE_RIGHT])
			Player1.move(1, 0);

		if (keyboard[SDL_SCANCODE_W])
			Player2.move(0, -1);
		if (keyboard[SDL_SCANCODE_S])
			Player2.move(0, 1);
		if (keyboard[SDL_SCANCODE_A])
			Player2.move(-1, 0);
		if (keyboard[SDL_SCANCODE_D])
			Player2.move(1, 0);

		Player2.update(deltaTime);
		Player1.update(deltaTime);

		for (std::vector<Carrot>::size_type i = 0; i < _carrots.size(); i++) {
			_carrots[i]->update(deltaTime);

			if (isColliding(&Player1, _carrots[i])) {
				Player1.setScore(1);
				Player2.incrementSpeed();

				/* Spawn them correctly*/
				while (collideWithOtherObjects(_carrots[i])) {
					_carrots[i]->relocate();
				}
			}

			if (isColliding(&Player2, _carrots[i])) {
				Player2.setScore(1);
				Player1.incrementSpeed();

				/* Spawn them correctly*/
				while (collideWithOtherObjects(_carrots[i])) {
					_carrots[i]->relocate();
				}
			}
		}
		for (std::vector<Flower_Dead>::size_type i = 0; i < _flowers_dead.size(); i++) {
			_flowers_dead[i]->update();

			/* Using else if, because if the first player touches the flower, flower will disappaer
			 * an there is no reason to check the same thing for the second player if flower is gone */
			if (isColliding(&Player1, _flowers_dead[i])) {
				_flowers_dead[i]->spawn(true);
				setEndMode(2, EndMode::NORMAL_END);

			} else if (isColliding(&Player2, _flowers_dead[i])) {
				_flowers_dead[i]->spawn(true);
				setEndMode(1, EndMode::NORMAL_END);
			}
		}
		for (std::vector<Flower_Slow>::size_type i = 0; i < _flowers_slow.size(); i++) {
			_flowers_slow[i]->update();

			/* Using else if, because if the first player touches the flower, flower will disappaer
			* an there is no reason to check the same thing for the second player if flower is gone */
			if (isColliding(&Player1, _flowers_slow[i])) {
				Player1.decrementSpeed(CFG::SPEED_DECREASE);

				/* Give more time to mad player */
				if (Player1.isMad())
					Player1.increasePoisonTime(CFG::POISON_TIME_INCREASE);

				/* Spawn them correctly*/
				while (collideWithOtherObjects(_flowers_slow[i])) {
					_flowers_slow[i]->spawn();
				}
			} else if (isColliding(&Player2, _flowers_slow[i])) {
				Player2.decrementSpeed(CFG::SPEED_DECREASE);

				/* Give more time to mad player */
				if (Player2.isMad())
					Player2.increasePoisonTime(CFG::POISON_TIME_INCREASE);

				/* Spawn them correctly*/
				while (collideWithOtherObjects(_flowers_slow[i])) {
					_flowers_slow[i]->spawn();
				}
			}
		}
		for (std::vector<Flower_Mad>::size_type i = 0; i < _flowers_mad.size(); i++) {
			_flowers_mad[i]->update();

			/* Using else if, because if the first player touches the flower, flower will disappaer
			* an there is no reason to check the same thing for the second player if flower is gone */
			if (isColliding(&Player1, _flowers_mad[i])) {
				_flowers_mad[i]->spawn(true);
				Player1.setMadMode(true);

			} else if (isColliding(&Player2, _flowers_mad[i])) {
				_flowers_mad[i]->spawn(true);
				Player2.setMadMode(true);
			}
		}
		for (std::vector<Flower_Inverted>::size_type i = 0; i < _flowers_inverted.size(); i++) {
			_flowers_inverted[i]->update();

			/* Using else if, because if the first player touches the flower, flower will disappaer
			* an there is no reason to check the same thing for the second player if flower is gone */
			if (isColliding(&Player1, _flowers_inverted[i])) {
				Player1.setInvertedControls(CFG::INVERTED_CONTROLS_TIME / 2);
				Player2.setInvertedControls(CFG::INVERTED_CONTROLS_TIME);

				/* Spawn them correctly*/
				while (collideWithOtherObjects(_flowers_inverted[i])) {
					_flowers_inverted[i]->spawn();
				}
			} else if (isColliding(&Player2, _flowers_inverted[i])) {
				Player1.setInvertedControls(CFG::INVERTED_CONTROLS_TIME / 2);
				Player2.setInvertedControls(CFG::INVERTED_CONTROLS_TIME);

				/* Spawn them correctly*/
				while (collideWithOtherObjects(_flowers_inverted[i])) {
					_flowers_inverted[i]->spawn();
				}
			}
		}
		for (std::vector<Flower_Speed>::size_type i = 0; i < _flowers_speed.size(); i++) {
			_flowers_speed[i]->update();

			/* Using else if, because if the first player touches the flower, flower will disappaer
			* an there is no reason to check the same thing for the second player if flower is gone */
			if (isColliding(&Player1, _flowers_speed[i])) {
				Player1.incrementSpeed();
				Player1.incrementSpeed();
				Player1.setScore(-2);

				/* Spawn them correctly*/
				while (collideWithOtherObjects(_flowers_speed[i])) {
					_flowers_speed[i]->spawn();
				}
			} else if (isColliding(&Player2, _flowers_speed[i])) {
				Player2.incrementSpeed();
				Player2.incrementSpeed();
				Player2.setScore(-2);

				/* Spawn them correctly*/
				while (collideWithOtherObjects(_flowers_speed[i])) {
					_flowers_speed[i]->spawn();
				}
			}
		}

		theEnd();
	}
}
void State_Gameplay::Render()
{
	/* Whole map */
	_level->render();

	/* Next two are rendered fonts for displaying score and speed */
	_font->setColor(CFG::PLAYER_FONT_1.r, CFG::PLAYER_FONT_1.g, CFG::PLAYER_FONT_1.b);
	_font->renderString(97, 5, std::to_string((int)Player1.getScore()));
	_font->renderString(194, 5, std::to_string((int)Player1.getSpeed()));

	_font->setColor(CFG::PLAYER_FONT_2.r, CFG::PLAYER_FONT_2.g, CFG::PLAYER_FONT_2.b);
	_font->renderString((_game->getWidth() / 2) + 97 - 135, 5, std::to_string((int)Player2.getScore()));
	_font->renderString((_game->getWidth() / 2) + 194 - 135, 5, std::to_string((int)Player2.getSpeed()));
	
	/*for (std::vector<Flower>::size_type i = 0; i < _flowers_dead.size(); i++) {
		_flowers_dead[i]->render();
	}*/

	Player1.render();
	Player2.render();

	/* This is here because player alter the color of the original font texture */
	_font->resetColor();


	for (std::vector<Carrot>::size_type i = 0; i < _carrots.size(); i++) {
		_carrots[i]->render();
	}
	for (std::vector<Flower_Dead>::size_type i = 0; i < _flowers_dead.size(); i++) {
		_flowers_dead[i]->render();
	}//removemybe and uncomment line 114 
	for (std::vector<Flower_Slow>::size_type i = 0; i < _flowers_slow.size(); i++) {
		_flowers_slow[i]->render();
	}
	for (std::vector<Flower_Mad>::size_type i = 0; i < _flowers_mad.size(); i++) {
		_flowers_mad[i]->render();
	}
	for (std::vector<Flower_Inverted>::size_type i = 0; i < _flowers_inverted.size(); i++) {
		_flowers_inverted[i]->render();
	}
	for (std::vector<Flower_Speed>::size_type i = 0; i < _flowers_speed.size(); i++) {
		_flowers_speed[i]->render();
	}
}
void State_Gameplay::Quit()
{
	for (std::vector<Carrot>::size_type i = 0; i < _carrots.size(); i++) {
		delete _carrots[i];
	}
	_carrots.clear();

	for (std::vector<Flower_Dead>::size_type i = 0; i < _flowers_dead.size(); i++) {
		delete _flowers_dead[i];
	}
	_flowers_dead.clear();

	for (std::vector<Flower_Slow>::size_type i = 0; i < _flowers_slow.size(); i++) {
		delete _flowers_slow[i];
	}
	_flowers_slow.clear();

	for (std::vector<Flower_Mad>::size_type i = 0; i < _flowers_mad.size(); i++) {
		delete _flowers_mad[i];
	}
	_flowers_mad.clear();

	for (std::vector<Flower_Inverted>::size_type i = 0; i < _flowers_inverted.size(); i++) {
		delete _flowers_inverted[i];
	}
	_flowers_inverted.clear();

	for (std::vector<Flower_Speed>::size_type i = 0; i < _flowers_speed.size(); i++) {
		delete _flowers_speed[i];
	}
	_flowers_speed.clear();
	
	delete _font;
	_font = NULL;

	delete _level;
	_level = NULL;

	delete _timer;//rrr
	_timer = NULL;//rrr

	delete _rm;
	_rm = NULL;
}

bool State_Gameplay::isColliding(Object* thisObject, Object* other)
{
	/* If they are the same object */
	if (thisObject == other) {
		return false;
	}
	else if (thisObject->collideWith(other)) {
		return true;
	}

	return false;
}
Player* State_Gameplay::getPlayer(int currnetPlayerIndex)
{
	if (currnetPlayerIndex == 1) {
		return &Player2;
	} else if (currnetPlayerIndex == 2) {
		return &Player1;
	} else {
		return NULL;
	}
}
void State_Gameplay::theEnd()
{
	/* Saving stats */
	_game->getStats()->SetP1Score(Player1.getScore());
	_game->getStats()->SetP2Score(Player2.getScore());
	_game->getStats()->SetGameplayTime(_timer->getTime());
	_game->getStats()->SetStateGameplayEnd(_endMode);

	if ((_endMode != EndMode::PLAY_MODE))  {
		SDL_SetRenderDrawColor(_game->getRenderer(), 83, 181, 100, CFG::PLAYER_1.a);
		SDL_RenderClear(_game->getRenderer());

		std::stringstream winnerText;
		winnerText << "Player " << _winner << " has won!";

		std::streamsize winSize = winnerText.str().size() * 64;
		_font->setColor(CFG::WHITE_COLOR.r, CFG::WHITE_COLOR.g, CFG::WHITE_COLOR.b);
		_font->renderString(_game->getWidth() / 4, _game->getHeight() / 4, winnerText.str(), 3);

		SDL_RenderPresent(_game->getRenderer());
		SDL_Delay(1000);
		
		_endMode = EndMode::FINISHED;
		_game->pushState(new State_End());
	}
}
void State_Gameplay::setEndMode(int winner, EndMode endMode)
{
	_winner = winner;

	if (winner == 1) {
		_game->getStats()->P1AddVictory();
	} else if (winner == 2) {
		_game->getStats()->P2AddVictory();
	}

	_endMode = endMode;
}
bool State_Gameplay::collideWithOtherObjects(Object* object)
{
	if (isColliding(object, &Player1) || isColliding(object, &Player2)) {
		return true;
	}

	for (std::vector<Flower_Dead>::size_type i = 0; i < _flowers_dead.size(); i++) {
		if (isColliding(object, _flowers_dead[i])) {
			return true;
		}
	}

	for (std::vector<Flower_Slow>::size_type i = 0; i < _flowers_slow.size(); i++) {
		if (isColliding(object, _flowers_slow[i])) {
			return true;
		}
	}

	for (std::vector<Flower_Mad>::size_type i = 0; i < _flowers_mad.size(); i++) {
		if (isColliding(object, _flowers_mad[i])) {
			return true;
		}
	}

	for (std::vector<Flower_Inverted>::size_type i = 0; i < _flowers_inverted.size(); i++) {
		if (isColliding(object, _flowers_inverted[i])) {
			return true;
		}
	}

	for (std::vector<Carrot>::size_type i = 0; i < _carrots.size(); i++) {
		if (isColliding(object, _carrots[i])) {
			return true;
		}
	}

	return false;
}