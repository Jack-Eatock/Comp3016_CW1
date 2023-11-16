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
	UiLabel(Vector2D pos, std::string text, std::string font, SDL_Color& colour, float _width, bool _centre = true) :
		labelText(text), labelFont(font), textColour(colour), width(_width)
	{
		centre = _centre;
		position.x = pos.X;
		position.y = pos.Y;
		SetLabelText(labelText, labelFont, true);
	}

	~UiLabel(){}

	void SetLabelText(std::string text, std::string font, bool setPos = false)
	{
		if (setPos) {
			targetPos = Vector2D(position.x, position.y);
		}

		SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(Game::assets->GetFont(font), text.c_str(), textColour, width);
		textTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_FreeSurface(surface);
		SDL_QueryTexture(textTexture, nullptr, nullptr, &position.w, &position.h); // Copies width and height from the texture.
		if (centre)
		{
			position.x = targetPos.X - position.w / 2;
			position.y = targetPos.Y - position.h / 2;
		}
	}

	void Draw() override  
	{
		SDL_RenderCopy(Game::renderer, textTexture, nullptr, &position);

		std::cout << "TEst" << position.w << std::endl;
	}

private:
	bool centre = true;
	Vector2D targetPos;
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColour;
	SDL_Texture* textTexture;
	float width;
};