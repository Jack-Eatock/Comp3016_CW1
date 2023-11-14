#pragma once

#include "Components.h"
#include "SDL.h"
#include "../Headers/Constants.h"
#include "../Headers/TextureManager.h"

class SpriteComponent : public Component 
{
private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;

	SpriteComponent(const char* path) 
	{
		SetText(path);
	}

	void SetText(const char* path) 
	{
		texture = TextureManager::LoadTexture(path);
	}

	void Init() override
	{
		position = &entity->GetComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 16;
		destRect.w = destRect.h = srcRect.w * SCALE_FACTOR;
	}

	void Update() override
	{
		destRect.x = position->X();
		destRect.y = position->Y();
	}

	void Draw() override 
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};