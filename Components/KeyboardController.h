#pragma once

#include "../Headers/Game.h"
#include "EntityComponentSystem.h"
#include "Components.h"



class KeyboardController : public Component 
{
public:
	TransformComponent* transform;

	bool up, down, left, right;

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
	}

	void Update() override
	{
		if (Game::event.type == SDL_MOUSEMOTION) 
		{
			transform->MousePos.X = Game::event.button.x;
			transform->MousePos.Y = Game::event.button.y;
		}

		// Keyboard
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				up = true;
				break;

			case SDLK_s:
				down = true;
				break;

			case SDLK_a:
				left = true;
				break;

			case SDLK_d:
				right = true;
				break;

			case SDLK_LSHIFT:
				transform->IsBoosting = true;
				break;

			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) 
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				up = false;
				break;

			case SDLK_s:
				down = false;
				break;

			case SDLK_a:
				left = false;
				break;

			case SDLK_d:
				right = false;
				break;

			case SDLK_LSHIFT:
				transform->IsBoosting = false;
				break;

			default:
				break;
			}
		}

		// X axis first
		if (left && right)
			transform->Input.X = 0;
		else if (left)
			transform->Input.X = -1;
		else if (right)
			transform->Input.X = 1;
		else
			transform->Input.X = 0;

		// Y axis
		if (up && down)
			transform->Input.Y = 0;
		else if (up)
			transform->Input.Y = -1;
		else if (down)
			transform->Input.Y = 1;
		else
			transform->Input.Y = 0;
	}
};
