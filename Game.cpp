#include "Game.h"

Game::Game()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
};

Game::~Game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::Run()
{
    while (true) 
    {
        Input();
        Render();
    }
}

void Game::Input()
{
    SDL_Event event;
    const Uint8* state = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&event)) {
        if (state[SDL_SCANCODE_X])
        {
            SDL_Quit();
            exit(0);
        }
        else {

            if (state[SDL_SCANCODE_UP]) {
                
            }

        }
    }
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect test = { 40, 40, 20, 20 };
    SDL_RenderFillRect(renderer, &test);
    SDL_RenderPresent(renderer);
    SDL_Delay(50);
}
