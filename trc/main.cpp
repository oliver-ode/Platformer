#include "game.hpp"

Game *game = nullptr;

int main(){
    game = new Game();

    game->init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    game->createPlayer(200, 200, 50, 50, {0, 255, 255, 255});

    while(game->running()){
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();

    return 0;    
}