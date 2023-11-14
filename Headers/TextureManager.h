#pragma once

#include "../Headers/Game.h"


class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileDir, SDL_Renderer* renderer);
};