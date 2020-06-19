#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <iostream>

#include "player.hpp"
#include "event_handler.hpp"

class Game{
    public:        
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

        void handleEvents();
        void update();
        void render();
        void clean();

        void createPlayer(int xpos, int ypos, int width, int height, SDL_Color color);

        bool running(){return isRunning;}
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        Player *player = new Player();
        bool playerMove = false;
        EventHandler *evh = new EventHandler();

        bool isRunning;
};

#endif