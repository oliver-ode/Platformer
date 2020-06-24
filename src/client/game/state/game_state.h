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

            virtual void handleInput() = 0; //parameters
            virtual void render() = 0; //parameters

            // Called when state is entered
            virtual void onEnter(){}

            // Called when state is exited
            virtual void onExit(){}
        protected:
            StateHandler *mp_stateHandler;
    };
}