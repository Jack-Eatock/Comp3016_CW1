#include "../Components/EnemyComponent.h"
#include "../Headers/Constants.h"
#include <random>
#include <iostream>
#include "../Components/Components.h"
#include "../Components/EntityComponentSystem.h"
#include "SDL.h"

void EnemyComponent::Collision(const ColliderComponent& collider)
{
	if (destroyed)
		return;

	if (collider.tag == "FriendlyBullet")
	{
		collider.entity->Destroy();
		health--;

		// Switch visual
		if (health == 2)
			entity->GetComponent<SpriteComponent>().SetText("EnemyShip_DMG1");

		else if (health == 1)
			entity->GetComponent<SpriteComponent>().SetText("EnemyShip_DMG2");

		else if (health <= 0)
			entity->GetComponent<SpriteComponent>().SetText("EnemyShip_DMG3");

		if (health <= 0)
		{
			TransformComponent* transform = &entity->GetComponent<TransformComponent>();
			transform->useInput = false;
			transform->rotateTowardsTarget = false;
			Game::Instance->PlayerDestroyedAShip();

			destroyed = true;
			timeOfDestroy = SDL_GetTicks();
		}
	}
}

void EnemyComponent::Fire()
{
	if (SDL_GetTicks() - timeOfLastShot < timeToReload)
		return;

	timeOfLastShot = SDL_GetTicks();
	std::string spriteId = "EnemyBullet";
	std::string colliderId = "EnemyBullet";
	Vector2D direction = transform->TargetPos;
	direction -= transform->Position;
	direction = direction.Normalise();

	float offset = 32;
	Vector2D startPos = transform->Position;
	startPos.Add(Vector2D(direction.X * offset, direction.Y * offset));
	Game::assets->SpawnBullet(startPos, 1000, 25, spriteId, colliderId, direction);
	
}

void EnemyComponent::UpdateLocal()
{
	if (destroyed) 
	{
		if (SDL_GetTicks() - timeOfDestroy > timeUntilDespawn) 
		{
			entity->Destroy();
		}
		return;
	}

	//std::cout << "AA " << initialDelay - spawnTime << std::endl;
	if (SDL_GetTicks() >  spawnTime + initialDelay ) {
		Fire();
	}

	if (headingToLocation) {

		// Have they reached the location?
		// chekc the distance from.
		float dist = transform->DistanceBetweenPoints(transform->Position, targetPos);
		//std::cout << id << " " << dist << " " << transform->Position << std::endl;

		Vector2D direction = targetPos;
		direction.Subtract(transform->Position);
		direction = direction.Normalise();

		transform->MovementInput = direction;

		if (dist < 20) 
			headingToLocation = false;

		Manager& temp = entity->manager;
		Entity& player1 = temp.GetEntity();

		transform->TargetPos = player1.GetComponent<TransformComponent>().Position;
	}

	else {
		std::mt19937 gen{ seed() }; // seed the generator

		std::uniform_int_distribution<> dist{ 30, WINDOW_WIDTH - 30 };
		int randX = dist(gen);

		std::uniform_int_distribution<> dist2{ 30, WINDOW_HEIGHT - 30 };
		int randY = dist2(gen);

		// Fly to location
		// Get direction to the location
		targetPos = Vector2D(randX, randY);

		Vector2D direction = targetPos;
		direction.Subtract(transform->Position);
		direction = direction.Normalise();

		transform->MovementInput = direction;

		headingToLocation = true;
	}
}

void EnemyComponent::InitLocal()
{
	std::mt19937 gen{ seed() }; // seed the generator
	std::uniform_int_distribution<> dist6{ 0, 4};
	
	initialDelay = dist6(gen) * 1000;
	std::cout << "AA " << initialDelay << std::endl;
	transform = &entity->GetComponent<TransformComponent>();
	spawnTime = SDL_GetTicks();
}
