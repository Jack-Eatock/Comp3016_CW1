#pragma once
#include "SDL.h"
#include <SDL_image.h>

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileDir);
	static void Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, double angle, SDL_Point* point, SDL_RendererFlip* flip);
};