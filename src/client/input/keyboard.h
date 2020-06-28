#pragma once

#include <SDL2/SDL.h>

#include <array>

namespace client{
    class Keyboard final{
        public:
            Keyboard();

            void update(SDL_Event e);
            bool isKeyDown(int keyCode) const;
            bool isKeyReleased(int keyCode) const;
        private:
            void resetKeys();
            
            int keySize = 123;
            std::array<bool, 123> m_keys;
            int m_recentlyReleased;
    };
}