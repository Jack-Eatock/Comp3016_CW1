#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Constants.h"
#include <vector>
#include "Vector2D.h"

class ColliderComponent;
class AssetManager;
class Entity;

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
	void PlayerDied();
	void PlayerDestroyedAShip();
	Entity* Player;

	static 	SDL_Renderer* renderer;
	static  SDL_Event event;
	static  std::vector<ColliderComponent*> colliders;
	static  AssetManager* assets;

private:
	void Restart();
	void StartGame();
	void StartNextWave();
	void SetupAssets();
	void SetupText();
	void CollisionDetection();
	bool isRunning;
	SDL_Window *window;

};


