#pragma once
#include <SDL.h>
#include "../Components/Components.h"

class CollisionDetection
{
public:

	static bool RectCollision_AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool RectCollision_AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};