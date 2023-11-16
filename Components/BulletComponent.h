#pragma once

#include "../Components//EntityComponentSystem.h"
#include "../Components/Components.h"

class BulletComponent : public Component
{
public:
	BulletComponent(int _range, int _speed, Vector2D _direction)
	{
		range = _range;
		speed = _speed;
		direction = _direction;
	}

	~BulletComponent() {

	}

	void Init() override 
	{
		transform = &entity->GetComponent<TransformComponent>();

		startPos = transform->Position;

		transform->useInput = false;
		transform->applyDrag = false;
		transform->rotateTowardsTarget = false;
		transform->keepWithinBounds = false;
	}

	void Update() override 
	{
		// Move the bullet towards the target (The player)
		distance = transform->DistanceBetweenPoints(transform->Position, startPos);
		Vector2D velocity = direction;
		velocity.Multiply(Vector2D(speed, speed));
		transform->Velocity = velocity;

		// If the bullet is out of range destroy it.
		if (distance > range)
			entity->Destroy();
	}

private:
	TransformComponent* transform;
	Vector2D startPos;
	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D direction = Vector2D(0,0);
};