#include "../Components/PlayerComponent.h"
#include "../Headers/Game.h"
#include "../Headers/AssetManager.h"
#include <string>
#include "../Components/Components.h"

void PlayerComponent::Fire()
{
	if (destroyed)
		return;

	std::string spriteId = "Bullet";
	std::string colliderId = "FriendlyBullet";
	Vector2D direction = transform->TargetPos;
	direction -= transform->Position;
	direction = direction.Normalise();

	float offset = 32;
	Vector2D startPos = transform->Position;
	startPos.Add(Vector2D(direction.X * offset, direction.Y * offset));
	Game::assets->SpawnBullet(startPos, 1000, 25, spriteId, colliderId, direction);
}

void PlayerComponent::Collision(const ColliderComponent& collider)
{
	if (destroyed)
		return;

	if (collider.tag == "EnemyBullet")
	{
		collider.entity->Destroy();
		health--;
		// Switch visual
		if (health == 2)
			entity->GetComponent<SpriteComponent>().SetText("FriendlyShip_DMG1");

		else if (health == 1)
			entity->GetComponent<SpriteComponent>().SetText("FriendlyShip_DMG2");

		else if (health <= 0)
			entity->GetComponent<SpriteComponent>().SetText("FriendlyShip_DMG3");

		if (health <= 0)
		{
			TransformComponent* transform = &entity->GetComponent<TransformComponent>();
			transform->useInput = false;
			transform->rotateTowardsTarget = false;
			Game::Instance->PlayerDied();
			destroyed = true;
		}
	}
}