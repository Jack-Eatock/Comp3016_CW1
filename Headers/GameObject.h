#pragma once
#include "../Headers/Game.h"

class GameObject 
{
public:
	GameObject(const char* _textureSheet, SDL_Renderer* _renderer, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:

	int xPos;
	int yPos;

	SDL_Texture* objectTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};