#pragma once
#include <SDL.h>


class CollisionDetection
{
public:

	static bool RectCollision_AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};