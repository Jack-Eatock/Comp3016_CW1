#pragma once
#include <string>
#include "SDL.h"
#include "EntityComponentSystem.h"
#include "Components.h"

class ColliderComponent : public Component 
{
public:
	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;

	/// <summary>
	/// The colliders are manually set. This is so we can have more generous colliders, so the player
	/// does not get frustrated when a bullet only just hits them. 
	/// </summary>
	ColliderComponent(int width, int height, std::string _tag)
	{
		collider.w = width;
		collider.h = height;
		tag = _tag;
	}

	void Init() override
	{
		if (!entity->HasComponent<TransformComponent>()) 
			entity->AddComponent<TransformComponent>();

		transform = &entity->GetComponent<TransformComponent>();

		Game::colliders.push_back(this);
	}
	
	void Update() override
	{
		collider.x = static_cast<int>(transform->Position.X);
		collider.y = static_cast<int>(transform->Position.Y);
	}
};
