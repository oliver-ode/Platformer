#pragma once

#include <stack>
#include <memory>

#include "game_state.h"

namespace client{
    // Manager class for the state of the game (main menu, playing)
    class StateHandler final{
        public:
            StateHandler();

            // Gets current state of game
            GameState &peekState;

            // Pushes a new state to the state handler
            template <typename State, typename... Args> void pushState(Args &&... args);

            // Removes the top game state
            void popState();

            void update();
            void clear();

            bool isEmpty() const;
        
        private:
            std::stack<std::unique_ptr<GameState>> m_gameStates;
            int m_popCount = 0;
    };

    template <typename State, typename... Args> void StateHandler::pushState(Args &&... args){
        m_gameStates.push(std::make_unique<State>(std::forward<Args>(args)...));
        peekState().onEnter();
    }
}