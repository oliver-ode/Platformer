#pragma once

#include <SDL2/SDL.h>

namespace client{
    class StateHandler;
    class Keyboard;
    class Renderer; //possibly not?

    // Base class for the different game states
    class GameState{
        public:
            GameState(StateHandler &stateHandler);
            virtual ~GameState() = default;

            virtual void handleKeyDown([[maybe_unused]] int keyCode){}
            virtual void handleKeyUp([[maybe_unused]] int keyCode){}

            virtual void handleInput(const Keyboard &keyboard, const SDL_Window &window) = 0; 
            virtual void update() = 0;
            virtual void render(Renderer &renderer) = 0;

            // Called when state is entered
            virtual void onEnter(){}

            // Called when state is exited
            virtual void onExit(){}
        protected:
            StateHandler *mp_stateHandler;
    };
}