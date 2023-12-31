#include <iostream>
#include "../Headers/Game.h"

Game* game = nullptr;
int main(int argc, char *argv[])
{
    const int fps = 60;
    const int frameDelay = 1000 / fps;
    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->Init("The Resiliance of Mankind", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);
    while (game->Running()) 
    {
        frameStart = SDL_GetTicks();

        game->HandleEvents();
        game->Update();
        game->Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) 
            SDL_Delay(frameDelay - frameTime);
    }
    game->Clean();
    return 0;
}

