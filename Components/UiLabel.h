#pragma once

#include "../Components/EntityComponentSystem.h"
#include "../Headers/AssetManager.h"
#include "../Headers/Game.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include "../Headers/Vector2D.h"


class UiLabel : public Component
{
public:
	UiLabel(Vector2D pos, std::string text , std::string font, SDL_Color& colour) :
		labelText(text), labelFont(font), textColour(colour)
	{
		position.x = pos.X;
		position.y = pos.Y;
		SetLabelText(labelText, labelFont);
	}

	~UiLabel(){}

	void SetLabelText(std::string text, std::string font)
	{
		SDL_Surface* surface = TTF_RenderText_Blended(Game::assets->GetFont(font), text.c_str(), textColour);
		textTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_FreeSurface(surface);
		SDL_QueryTexture(textTexture, nullptr, nullptr, &position.w, &position.h); // Copies width and height from the texture.
	}

	void Draw() override  
	{
		SDL_RenderCopy(Game::renderer, textTexture, nullptr, &position);
	}

private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColour;
	SDL_Texture* textTexture;
};