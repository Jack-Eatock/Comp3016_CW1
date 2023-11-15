#include "../Headers/Game.h"
#include "../Headers/TextureManager.h"
#include "../Components/Components.h"
#include <iostream>
#include "../Headers/Vector2D.h"
#include "../Headers/CollisionDetection.h"

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.AddEntity()); // Create Player Entity
auto& player2(manager.AddEntity()); // Other Player

Game::Game() {};
Game::~Game() {}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) 
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initiated!" << std::endl;

		// Create Window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
			std::cout << "Window created!" << std::endl;

		// Create Renderer
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) 
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		// Run the 
		isRunning = true;
	}
	else
		std::cout << "[ERROR] Subsystems failed to Initialise!" << std::endl;

	player.AddComponent<TransformComponent>(50, 50);
	player.AddComponent<SpriteComponent>("Assets/UpdatedShip.png");
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>(32, 32, "Player");
	player.AddComponent<PlayerComponent>();

	player2.AddComponent<TransformComponent>(400, 200);
	player2.AddComponent<SpriteComponent>("Assets/UpdatedShip.png");
	player2.AddComponent<ColliderComponent>(32, 32, "Enemy");
	player2.AddComponent<EnemyComponent>();
	
}

void Game::HandleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			std::cout << "Input Registered: 'Quit' " << std::endl;
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::Update()
{
	manager.Refresh();
	manager.Update();

	for (auto colider : Game::colliders)
	{
		for (auto colider2 : Game::colliders)
		{
			if (colider == colider2)
				continue;

			CollisionDetection::RectCollision_AABB(*colider, *colider2);
		}
	}
}

void Game::Render() 
{
	SDL_RenderClear(renderer);

	manager.Draw();

	SDL_RenderPresent(renderer);
}

void Game::Clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned " << std::endl;
}
