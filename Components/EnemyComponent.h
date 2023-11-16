
#pragma once
#include "SDL.h"
#include "EntityComponentSystem.h"
#include "../Headers/CollisionDetection.h"
#include <random>

class EnemyComponent : public Component
{
public:

	void Update() override
	{
		UpdateLocal();
	}

	void Init() override 
	{ 
		
		InitLocal();
	}

	void InitLocal();

	void UpdateLocal();

	void Collision(const ColliderComponent& collider);

	void Fire();

private: 
		std::random_device seed;
		std::mt19937 gen;
		TransformComponent* transform;
		bool headingToLocation = false;
		Vector2D targetPos;
		float timeOfLastShot;
		float timeToReload = 1000/2;
		float initialDelay = 0;
		float spawnTime = 0;
		int health = 3;
		bool destroyed = false;
		float timeOfDestroy = 0;
		float timeUntilDespawn = 3 * 1000;

};