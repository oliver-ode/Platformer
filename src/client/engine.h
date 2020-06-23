#pragma once

#include <SDL2/SDL.h>

struct LaunchConfig;

namespace client{
    class Engine final{
        public:
            enum class Status {
                Ok = 10,
                Exit = 11,
                GLInitError = 20,
            };
            Engine(const LaunchConfig &config);
            Status runClient();
        private:
            void handleWindowEvents();
            void handleInput();
            void update();
            void render();

            void exit();

            SDL_Window *window;
            SDL_Renderer *renderer;
    };
}