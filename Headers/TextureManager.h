#pragma once

#include "../Headers/Game.h"


class TextureManager
{
public:
	static void init(SDL_Renderer* renderer);
	static SDL_Texture* LoadTexture(const char* fileDir);
	static void Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);
};