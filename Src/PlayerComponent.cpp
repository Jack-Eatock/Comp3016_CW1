#include "../Components/PlayerComponent.h"
#include "../Headers/Game.h"

void PlayerComponent::Fire()
{
	std::cout << "Bang" << std::endl;

	Game::Instance->SpawnBullet(transform->Position, transform->Angle);
}

void PlayerComponent::Collision(const ColliderComponent& collider)
{
	std::cout << "AAAAA" << std::endl;
	
}