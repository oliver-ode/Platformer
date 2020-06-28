#pragma once

#include "game_state.h"

#include "../../../common/network/input_state.h"
#include "../../../common/types.h"

#include "../../network/client.h"

namespace client{
    class StateHandler;
    class Keyboard;
    class Renderer;

    // Actual playing state of game
    class PlayingState final : public GameState{
        public:
            PlayingState(StateHandler &stateHandler);

            void handleKeyUp(int keyCode) override;

            void handleInput(const Keyboard &keyboard, const SDL_Window &window) override;
            void update() override;
            void render(Renderer &render) override;

            void onExit() override;
        private:
            Entity &getPlayerEntity();

            EntityArray m_entities;
            Client m_client;
            Input m_inputState = 0;

            bool m_sentEmpty = false;
    };
}