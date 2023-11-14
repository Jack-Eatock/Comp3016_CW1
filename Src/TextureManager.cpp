#include "../Headers/TextureManager.h"
#include "../Headers/Game.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileDir)
{
	SDL_Surface* tmpSurface = IMG_Load(fileDir);
	SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return tmpTexture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, double angle, SDL_Point* point, SDL_RendererFlip* flip)
{
	SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &destRect, angle, point, *flip);
}