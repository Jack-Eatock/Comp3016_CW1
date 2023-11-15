#pragma once
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "../Components/EntityComponentSystem.h"
#include <map>
#include "SDL.h"

class AssetManager
{
public:
	AssetManager(Manager* manager);
	~AssetManager();
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);
private:

	Manager* manager;

	//  Basically a dictionairy.
	std::map<std::string, SDL_Texture*> textures;
};