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
		// Destroy the bullet that hit this ship.
		collider.entity->Destroy();
		health--;

		// Switch visual to show slightly damaged ship.
		if (health == 2)
			entity->GetComponent<SpriteComponent>().SetText("EnemyShip_DMG1");

		// Switch visual to show very damaged ship.
		else if (health == 1)
			entity->GetComponent<SpriteComponent>().SetText("EnemyShip_DMG2");

		// The ship has been destroyed.
		if (health <= 0)
		{
			// Switch visual to show destroyed ship.
			entity->GetComponent<SpriteComponent>().SetText("EnemyShip_DMG3");
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
	// Limit fire rate. Check if the time  since last shot is more than the reload time.
	if (SDL_GetTicks() - timeOfLastShot < timeToReload)
		return;

	timeOfLastShot = SDL_GetTicks();
	std::string spriteId = "EnemyBullet";
	std::string colliderId = "EnemyBullet";
	Vector2D direction = transform->TargetPos;
	direction -= transform->Position;
	direction = direction.Normalise();

	// Offset the bullet from the ship. So it spawns in front etc.
	float offset = 32;
	Vector2D startPos = transform->Position;
	startPos.Add(Vector2D(direction.X * offset, direction.Y * offset));
	Game::assets->SpawnBullet(startPos, 1000, 25, spriteId, colliderId, direction);
}

void EnemyComponent::UpdateLocal()
{
	if (destroyed) 
	{
		// Wait a couple seconds showing the destroyed ship before despawning.
		if (SDL_GetTicks() - timeOfDestroy > timeUntilDespawn) 
			entity->Destroy();
		return;
	}

	// Adds a delay to the ships first shot. 
	if (SDL_GetTicks() >  spawnTime + initialDelay ) {
		Fire();
	}

	// The ai flies to a location.
	if (headingToLocation) {

		// Have they reached the location?
		float dist = transform->DistanceBetweenPoints(transform->Position, targetPos);
		Vector2D direction = targetPos;
		direction.Subtract(transform->Position);
		direction = direction.Normalise();

		transform->MovementInput = direction;

		// If they are close enough, count it as them reaching the location. pick a new one.
		if (dist < 20) 
			headingToLocation = false;

		// Move towards the location.
		transform->TargetPos = Game::Instance->Player->GetComponent<TransformComponent>().Position;
	}

	// Choose a location for the ai to fly to.
	else {
		// Generate random coords to fly to.
		std::mt19937 gen{ seed() }; // seed the generator
		std::uniform_int_distribution<> dist{ 30, WINDOW_WIDTH - 30 };
		int randX = dist(gen);
		std::uniform_int_distribution<> dist2{ 30, WINDOW_HEIGHT - 30 };
		int randY = dist2(gen);

		// Pick a random location to fly to
		targetPos = Vector2D(randX, randY);
		Vector2D direction = targetPos;
		direction.Subtract(transform->Position);
		direction = direction.Normalise();
		transform->MovementInput = direction;

		// Location set, now start flying there.
		headingToLocation = true;
	}
}

void EnemyComponent::InitLocal()
{
	std::mt19937 gen{ seed() }; // seed the generator
	std::uniform_int_distribution<> dist6{ 1, 6};
	
	initialDelay = dist6(gen) * 1000;
	transform = &entity->GetComponent<TransformComponent>();
	spawnTime = SDL_GetTicks();
}
