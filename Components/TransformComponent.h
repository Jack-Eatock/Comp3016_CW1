#pragma once

#include "EntityComponentSystem.h"
#include "../Headers/Vector2D.h"
#include "SDL.h"
#include "../Headers/Constants.h"

class TransformComponent : public Component
{

public:
	
	double Angle;
	Vector2D MovementInput;
	Vector2D Position;
	Vector2D Velocity;
	bool IsBoosting = false;
	float TmpMaxSpeed = 0.00f;
	double Speed = 0.00f;
	Vector2D TargetPos;

	// Default constructor
	TransformComponent()
	{
		Position.X = 0.0f;
		Position.Y = 0.0f;
	}

	TransformComponent(float x, float y)
	{
		Position.X = x;
		Position.Y = y;
	}

	void Init() override 
	{
		Velocity.X = 0;
		Velocity.Y = 0;
	}

	void Update() override
	{
		CalculateMovement();
		ApplyDrag();
		
		// Calculate the magnitude using the formula: sqrt(X^2 + Y^2 + Z^2)
		Speed = sqrt(Velocity.X * Velocity.X + Velocity.Y * Velocity.Y);

		KeepWithinBounds();

		Position.X += Velocity.X;
		Position.Y += Velocity.Y;

		RotateTowardsTarget();

		//std::cout << "here " << Position << " a " << Speed << std::endl;
	}

	void CalculateMovement()
	{
		Vector2D normalisedInput = MovementInput.Normalise();

		// Apply Input
		Velocity.X = Velocity.X + (normalisedInput.X * ACCELERATION);
		Velocity.Y = Velocity.Y + (normalisedInput.Y * ACCELERATION);
	}

	void ApplyDrag()
	{
		// Apply Drag
		if (Velocity.X > 0.1)
		{
			if (Velocity.X - DRAG < 0)
				Velocity.X = 0;
			else
				Velocity.X -= DRAG;
		}
		else if (Velocity.X < 0.1)
		{
			if (Velocity.X + DRAG > 0)
				Velocity.X = 0;
			else
				Velocity.X += DRAG;
		}
		else
			Velocity.X = 0;

		if (Velocity.Y > 0.1)
		{
			if (Velocity.Y - DRAG < 0)
				Velocity.Y = 0;
			else
				Velocity.Y -= DRAG;
		}
		else if (Velocity.Y < 0.1)
		{
			if (Velocity.Y + DRAG > 0)
				Velocity.Y = 0;
			else
				Velocity.Y += DRAG;
		}
		else
			Velocity.Y = 0;
	}

	void KeepWithinBounds()
	{
		// If they go out of bounds, push them back.
		float bounceBackSpeed = Speed + BOUNCEOFWALL;
		if (Speed < BOUNCEOFWALL)
			bounceBackSpeed = BOUNCEOFWALL * ACCELERATION;

		// Left
		if (Position.X < 0)
			Velocity.X += bounceBackSpeed;

		// Right
		else if (Position.X > WINDOW_WIDTH - 50)
			Velocity.X -= bounceBackSpeed;

		// Up
		if (Position.Y < 0)
			Velocity.Y += bounceBackSpeed;

		// Down
		else if (Position.Y > WINDOW_HEIGHT - 50)
			Velocity.Y -= bounceBackSpeed;

		// Limiting speed;
		if (IsBoosting)
			TmpMaxSpeed = MAXSPEEDBOOSTING;
		else
			TmpMaxSpeed = MAXSPEED;

		if (Speed > TmpMaxSpeed)
		{
			// Use the normalised values to cap the velocity.
			Vector2D normalisedVelocity = Velocity.Normalise();
			Velocity.X = normalisedVelocity.X * TmpMaxSpeed;
			Velocity.Y = normalisedVelocity.Y * TmpMaxSpeed;
			Speed = sqrt(Velocity.X * Velocity.X + Velocity.Y * Velocity.Y);
		}
	}

	void RotateTowardsTarget()
	{
		// Calculate the angle of the ship. Look at direction from ship to mouse pos.
		float radAngle = atan2(TargetPos.Y - Position.Y, TargetPos.X - Position.X);
		Angle = (radAngle * 180 / M_PI);
	}
};