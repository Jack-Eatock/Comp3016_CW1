#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Constants.h"
#include <vector>
#include "Vector2D.h"

class ColliderComponent;
class AssetManager;

class Game
{
public:

	static Game* Instance;

	Game();
	~Game();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	bool Running() { return isRunning; }
	void SpawnBullet(Vector2D startPos, double angle);

	static 	SDL_Renderer* renderer;
	static  SDL_Event event;
	static  std::vector<ColliderComponent*> colliders;
	static  AssetManager* assets;

private:
	bool isRunning;
	SDL_Window *window;
};


