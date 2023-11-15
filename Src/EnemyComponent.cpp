#include "../Components/EnemyComponent.h"

void EnemyComponent::Collision(const ColliderComponent& collider)
{
	std::cout << "bbb" << std::endl;

	if (collider.tag == "Player")
	{
		entity->Destroy();
	}
}