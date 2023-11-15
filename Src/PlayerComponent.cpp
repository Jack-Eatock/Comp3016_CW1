#include "../Components/PlayerComponent.h"
#include "../Headers/Game.h"
#include "../Headers/AssetManager.h"
#include <string>

void PlayerComponent::Fire()
{
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
	if (collider.tag == "EnemyBullet")
	{
		collider.entity->Destroy();
		Game::Instance->PlayerHit();
	}
}