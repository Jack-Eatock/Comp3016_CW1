#pragma once

#include "../Components/EntityComponentSystem.h"

class PositionComponent : public Component
{
private:
	int xPos, yPos;

public:

	int X() { return xPos; }
	int Y() { return yPos; }

	// Default constructor
	PositionComponent() 
	{
		xPos = 0;
		yPos = 0;
	}

	PositionComponent(int x, int y)
	{
		xPos = x;
		yPos = y;
	}

	void Update() override
	{
		xPos++;
		yPos++;
	}

	void SetPos(int x, int y)
	{
		xPos = x;
		yPos = y;
	}
};