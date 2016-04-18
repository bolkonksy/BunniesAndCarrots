#include "ResourceManager.h"

#include "Game.h"

ResourceManager::ResourceManager(Game* game)
{
	_game = game;
}

ResourceManager::~ResourceManager()
{
	auto i = _textures.begin();
	while (i != _textures.end()) {
		SDL_DestroyTexture(i->second);
		i++;
	}
	_textures.clear();
}

void ResourceManager::loadTexture(const std::string filePath)
{
	SDL_Texture* newTexture = NULL;
	newTexture = IMG_LoadTexture(_game->getRenderer(), filePath.c_str());

	if (NULL == newTexture) {
		throw std::runtime_error("Error while loading texture " + filePath);
	}

	_textures.insert(std::pair<std::string, SDL_Texture*>(filePath, newTexture));
}

SDL_Texture* ResourceManager::getTexture(const std::string filePath)
{
	SDL_Texture* texture = NULL;
	auto i = _textures.find(filePath);

	texture = i->second;

	return texture;
}
