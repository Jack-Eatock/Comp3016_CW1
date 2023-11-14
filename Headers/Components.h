#pragma once

#include "../Headers/EntityComponentSystem.h"

class PositionComponent : public Component 
{
private:
	int xPos, yPos;

public:

	int X() { return xPos; }
	int Y() { return yPos; }

	void Init() override
	{
		xPos = 0;
		yPos = 0;
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