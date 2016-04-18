#include "State_Menu.h"


bool State_Menu::Init(Game* game)
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

	_blinking = 0.0f;

	return true;
}
void State_Menu::HandleEvents(SDL_Event* event)
{
	if (event->type == SDL_QUIT)
		_game->setQuit();
	else if (event->type == SDL_KEYDOWN) {
		if (event->key.keysym.sym == SDLK_ESCAPE)
			_game->popState();
	} 
}
void State_Menu::Update(float deltaTime)
{
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);

	if (keyboard[SDL_SCANCODE_SPACE]) {
		_game->pushState(new State_Gameplay());
	}

	_blinking += 2 * deltaTime;
	if (_blinking > 2.0f)
		_blinking = 0.0f;
}
void State_Menu::Render()
{
	std::string text = "PRESS SPACEBAR TO START";
	unsigned int x = text.length() * 8 / 2;
	
	if ((int)_blinking == 1)
		_font->renderString(_game->getWidth() / 2 - 3 * x, _game->getHeight() / 3, text, 3);

	text = "BUNNIES&CARROTS!";
	x = text.length() * 8 / 2;
	_font->renderString(_game->getWidth() / 2 - 3 * x, _game->getHeight() / 2, text, 3);
}
void State_Menu::Quit()
{
	delete _font;
	_font = NULL;
	delete _rm;
	_rm = NULL;
}

/* Unnecessary for this state - inherited functions */
bool State_Menu::isColliding(Object* thisObject, Object* other)
{
	return false;
}
Player* State_Menu::getPlayer(int playerIndex)
{
	return NULL; 
}
void State_Menu::setEndMode(int winner, EndMode endMode)
{

}
