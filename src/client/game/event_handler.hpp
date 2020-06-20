#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include <SDL2/SDL.h>
#include <iostream>

class EventHandler{
    public:
        EventHandler();
        ~EventHandler();

        int handleEvent(SDL_Event event);
        bool keyPressed(int keyCode);
        bool keyReleased(int keyCode);
        bool keyPairPressed(int keyCode1, int keyCode2);
    private:
        int keySize = 123;
        bool keyState[123] = {false};
        /* 
        Key codes for reference
        https://wiki.libsdl.org/SDLKeycodeLookup 
        */
};

#endif