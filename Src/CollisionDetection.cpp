#include "../Headers/CollisionDetection.h"

bool CollisionDetection::RectCollision_AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	//  Check if the two sqaure colliders are overlapping.
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
		if (colA.tag == "Player")
		{
			// The player has collided with something. Inform the player of the collision.
			if (colA.entity->HasComponent<PlayerComponent>())
				colA.entity->GetComponent<PlayerComponent>().Collision(colB);
		}
		else if (colA.tag == "Bullet")
		{
			
		}
		else if (colA.tag == "Enemy")
		{
			// An enemy has collided with something. Inform the enemy of the collision.
			if (colA.entity->HasComponent<EnemyComponent>())
				colA.entity->GetComponent<EnemyComponent>().Collision(colB);
		}

		return true;
	}
	return false;
}
