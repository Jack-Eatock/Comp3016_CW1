#include "../Components/EnemyComponent.h"
#include "../Headers/Constants.h"
#include <random>
#include <iostream>
#include "../Components/Components.h"
#include "../Components/EntityComponentSystem.h"

void EnemyComponent::Collision(const ColliderComponent& collider)
{
	if (collider.tag == "FriendlyBullet")
	{
		entity->Destroy();
		collider.entity->Destroy();
	}
}

void EnemyComponent::Fire()
{
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


		std::uniform_int_distribution<> dist3{ 0, 4 };
		int shouldIShoot = dist3(gen);

		if (shouldIShoot == 1) {
			Fire();
		}

		//std::cout << "Pos " << transform->Position << " Target" << targetPos <<  " " << direction << std::endl;
	}
	
}

void EnemyComponent::InitLocal()
{
	std::mt19937 gen{ seed() }; // seed the generator

	transform = &entity->GetComponent<TransformComponent>();
}
