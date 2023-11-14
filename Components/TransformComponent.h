#pragma once

#include "../Components/EntityComponentSystem.h"
#include "../Headers/Vector2D.h"

class TransformComponent : public Component
{

public:

	Vector2D Input;
	Vector2D Position;
	Vector2D Velocity;
	
	bool IsBoosting = false;
	float TmpMaxSpeed = 0.00f;
	double Speed = 0.00f;

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
		Vector2D normalisedInput = Input.Normalise();

		// Apply Input
		Velocity.X = Velocity.X + (normalisedInput.X * ACCELERATION);
		Velocity.Y = Velocity.Y + (normalisedInput.Y * ACCELERATION);

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

		// Calculate the magnitude using the formula: sqrt(X^2 + Y^2 + Z^2)
		Speed = sqrt(Velocity.X * Velocity.X + Velocity.Y * Velocity.Y);

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

		Position.X += Velocity.X;
		Position.Y += Velocity.Y;

		std::cout << "here " << Input << " a " << Speed << std::endl;
	}
};