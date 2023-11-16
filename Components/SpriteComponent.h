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

	SpriteComponent() {}

	SpriteComponent(std::string assetID) 
	{
		SetText(assetID);
	}

	~SpriteComponent() {}

	/// <summary>
	/// Switches the image shown for a specific entity. 
	/// E.g switch a ship for a damaged ship texture.
	/// </summary>
	/// <param name="assetID"></param>
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

	/// <summary>
	/// Moves the image to the position of the entity.
	/// </summary>
	void Update() override
	{
		destRect.x = transform->Position.X;
		destRect.y = transform->Position.Y;
	}

	/// <summary>
	/// Displays the texture to the screen.
	/// </summary>
	void Draw() override 
	{
		TextureManager::Draw(texture, srcRect, destRect, transform->Angle, NULL, &flip);
	}
};