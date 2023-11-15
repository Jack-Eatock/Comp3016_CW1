#pragma once

#include "../Headers/TextureManager.h"
#include "TransformComponent.h"
#include "SDL.h"
#include "../Headers/Constants.h"
#include "../Headers/AssetManager.h"
#include "../Headers/Game.h"

class SpriteComponent : public Component 
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	SDL_RendererFlip flip;

public:

	SpriteComponent() 
	{

	}

	SpriteComponent(std::string assetID) 
	{
		SetText(assetID);
	}

	~SpriteComponent() 
	{
	
	}

	void SetText(std::string assetID)
	{
		texture = Game::assets->GetTexture(assetID);
	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h =  PIXEL_RES;
		destRect.w = destRect.h = srcRect.w * SCALE_FACTOR;
		flip = SDL_FLIP_NONE;
	}

	void Update() override
	{
		destRect.x = transform->Position.X;
		destRect.y = transform->Position.Y;
	}

	void Draw() override 
	{
		TextureManager::Draw(texture, srcRect, destRect, transform->Angle, NULL, &flip);
	}
};