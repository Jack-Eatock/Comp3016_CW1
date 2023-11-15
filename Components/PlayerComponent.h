#pragma once
#include "EntityComponentSystem.h"
#include "ColliderComponent.h"

class PlayerComponent : public Component 
{
public:


	TransformComponent* transform;

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
	}


	void Update() override 
	{
		//// Mouse Click
		//if (Game::event.type == SDL_MOUSEBUTTONDOWN)
		//{
		//	Fire();
		//}
	}

	void Fire();

	void Collision(const ColliderComponent& collider);
};