#include <iostream>
#include "SDL.h"
#include "../Headers/Game.h"
Game* game = nullptr;

int main(int argc, char *argv[])
{
 
    game = new Game();
    game->Init("The Resiliance of Mankind", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    while (game->Running()) 
    {
        game->HandleEvents();
        game->Update();
        game->Render();
    }

    game->Clean();

    return 0;
}
