#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <string>

class Game;

class ResourceManager {
private:
	Game* _game;
	std::map<std::string, SDL_Texture*> _textures;

public:
	/* NO DEFAULT CONSTRUCTOR */
	ResourceManager(Game* game);
	~ResourceManager();

	/* Not a bool type, bc it throws an exception if it fails */
	void loadTexture(const std::string filePath);
	
	SDL_Texture* getTexture(const std::string filePath);
};

#endif