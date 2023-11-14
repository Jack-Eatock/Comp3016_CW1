#include "../Headers/TextureManager.h"
#include "../Headers/Game.h"


SDL_Renderer* renderer;

void TextureManager::init(SDL_Renderer* _renderer)
{
	renderer = _renderer;
}

SDL_Texture* TextureManager::LoadTexture(const char* fileDir)
{
	SDL_Surface* tmpSurface = IMG_Load(fileDir);
	SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return tmpTexture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect) 
{
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}