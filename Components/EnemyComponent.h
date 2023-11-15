
#pragma once
#include "SDL.h"
#include "EntityComponentSystem.h"
#include "../Headers/CollisionDetection.h"

class EnemyComponent : public Component
{
public:

	void Update() override
	{

	}

	void Collision(const ColliderComponent& collider);
};