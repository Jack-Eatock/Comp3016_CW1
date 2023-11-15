#include "../Headers/CollisionDetection.h"
#include "../Components/Components.h"


bool CollisionDetection::RectCollision_AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		)
	{
		// Collision  detected
		return  true;
	}
	return false;
}

bool CollisionDetection::RectCollision_AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (RectCollision_AABB(colA.collider, colB.collider))
	{
		//std::cout << colA.tag << " hit : " << colB.tag << std::endl;
		
		if (colA.tag == "Player")
		{
			if (colA.entity->HasComponent<PlayerComponent>())
				colA.entity->GetComponent<PlayerComponent>().Collision(colB);
		}
		else if (colA.tag == "Bullet")
		{
			
		}
		else if (colA.tag == "Enemy")
		{
			if (colA.entity->HasComponent<EnemyComponent>())
				colA.entity->GetComponent<EnemyComponent>().Collision(colB);
		}

		return true;
	}
	return false;
}
