#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Constants.h"
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	bool Running() { return isRunning; }

	static 	SDL_Renderer* renderer;
	static  SDL_Event event;
	static  std::vector<ColliderComponent*> colliders;

private:
	bool isRunning;
	SDL_Window *window;
};


