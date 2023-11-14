#include "../Headers/TextureManager.h"


SDL_Texture* TextureManager::LoadTexture(const char* fileDir, SDL_Renderer* renderer)
{
	SDL_Surface* tmpSurface = IMG_Load(fileDir);
	SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return tmpTexture;
}