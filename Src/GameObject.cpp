#include "../Headers/GameObject.h"
#include "../Headers/TextureManager.h"

GameObject::GameObject(const char* _textureSheet, SDL_Renderer* _renderer, int x, int y)
{
	renderer = _renderer;
	objectTexture = TextureManager::LoadTexture(_textureSheet, renderer);
	xPos = x;
	yPos = y;
}

void GameObject::Update() 
{
	xPos++;
	yPos++;

	srcRect.h = 16;
	srcRect.w = 16;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xPos;
	destRect.y = yPos;
	destRect.w = srcRect.w * SCALE_FACTOR;
	destRect.h = srcRect.h * SCALE_FACTOR;
}

void GameObject::Render()
{
	SDL_RenderCopy(renderer, objectTexture, &srcRect, &destRect);
}

