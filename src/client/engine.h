#pragma once

#include <SDL2/SDL.h>
#include "input/keyboard.h"
#include "game/state/state_handler.h"
#include "renderer/renderer.h"
#include "util/fps_counter.h"

namespace client{
    class Engine final{
        public:
            enum class Status {
                Ok = 10,
                Exit = 11,
                GLInitError = 20,
            };
            Engine();
            Status runClient();
        private:
            void handleWindowEvents();
            void handleInput();
            void update();
            void render();

            void exit();

            SDL_Window *m_window;
            SDL_Renderer *m_rendererSDL;
            Keyboard m_keyboard;
            Status m_status;

            StateHandler m_stateHandler;
            GameState *mp_currentState = nullptr;

            std::unique_ptr<Renderer> m_renderer;

            bool m_fullscreen = false;
    };
}