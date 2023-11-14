#include "../Headers/Game.h"
#include "../Headers/TextureManager.h"
#include "../Headers/GameObject.h"
#include "../Headers/EntityComponentSystem.h"
#include "../Headers/Components.h"
#include <iostream>

GameObject* player;

Game::Game() {};
Game::~Game() {}

Manager manager;
auto& newPlayer(manager.AddEntity()); // Create Player

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
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		
		// Run the 
		isRunning = true;
	}
	else
		std::cout << "[ERROR] Subsystems failed to Initialise!" << std::endl;

	player = new GameObject("Assets/Ship.png", renderer, 0, 0);
	newPlayer.AddComponent<PositionComponent>();


}

void Game::HandleEvents()
{
	SDL_Event event;
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
	player->Update();

	manager.Update();
	std::cout << newPlayer.GetComponent<PositionComponent>().X() << "," <<
		newPlayer.GetComponent<PositionComponent>().Y() << std::endl;
}

void Game::Render() 
{
	SDL_RenderClear(renderer);

	player->Render();
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

