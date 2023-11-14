#include "../Headers/Game.h"
#include <iostream>

SDL_Texture* playerTex;
SDL_Rect srcR, destR;

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
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}


		SDL_Surface* tmpSurface = IMG_Load("Assets/Ship.png");
		playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);

		// Run the 
		isRunning = true;
	}
	else
		isRunning = false;
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

int cntr;
void Game::Update() 
{
	cntr++;
	destR.h = 16 * SCALE_FACTOR;
	destR.w = 16 * SCALE_FACTOR;

	destR.x = 800 - cntr / 100;
}

void Game::Render() 
{
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, playerTex, NULL, &destR);

	SDL_RenderPresent(renderer);
}

void Game::Clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned " << std::endl;
}

