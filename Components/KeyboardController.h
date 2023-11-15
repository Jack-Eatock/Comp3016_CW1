#pragma once

#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "../Headers/Game.h"

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
		// Mouse Move
		if (Game::event.type == SDL_MOUSEMOTION) 
		{
			transform->TargetPos.X = Game::event.button.x;
			transform->TargetPos.Y = Game::event.button.y;
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
			transform->MovementInput.X = 0;
		else if (left)
			transform->MovementInput.X = -1;
		else if (right)
			transform->MovementInput.X = 1;
		else
			transform->MovementInput.X = 0;

		// Y axis
		if (up && down)
			transform->MovementInput.Y = 0;
		else if (up)
			transform->MovementInput.Y = -1;
		else if (down)
			transform->MovementInput.Y = 1;
		else
			transform->MovementInput.Y = 0;
	}
};
