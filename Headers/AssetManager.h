#pragma once
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "../Components/EntityComponentSystem.h"
#include <map>
#include "SDL.h"
#include "SDL_ttf.h"

class AssetManager
{
public:
	AssetManager(Manager* manager);
	~AssetManager();
	void AddTexture(std::string id, const char* path);

	void AddFont(std::string id, std::string path, int fontSize);
	TTF_Font* GetFont(std::string id);

	void SpawnBullet(Vector2D startPos, int range, int speed, std::string spriteId, std::string colliderId, Vector2D direction);
	SDL_Texture* GetTexture(std::string id);

private:

	Manager* manager;

	//  Basically a dictionairy.
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
};