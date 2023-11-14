#pragma once

#include "SDL.h"
#include "Constants.h"

class Game
{
public:
	Game();
	~Game();
	void Run();
private:
	void Input();
	void Render();
	SDL_Window* window;
	SDL_Renderer* renderer; 
};


