#include "../Components/PlayerComponent.h"
#include "../Headers/Game.h"
#include "../Headers/AssetManager.h"
#include <string>

void PlayerComponent::Fire()
{
	std::cout << "Bang" << std::endl;
	std::string test = "aa";
	Vector2D direction = transform->TargetPos;
	direction -= transform->Position;
	direction = direction.Normalise();

	float offset = 32;
	Vector2D startPos = transform->Position;
	startPos.Add(Vector2D(direction.X * offset, direction.Y * offset));
	Game::assets->SpawnBullet(startPos, 1000, 17, test, direction);
}

void PlayerComponent::Collision(const ColliderComponent& collider)
{
	std::cout << "AAAAA" << std::endl;
	
}