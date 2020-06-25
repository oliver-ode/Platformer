#include "engine.h"

#include <iostream>

#include "game/state/playing_state.h"

namespace client{
    Engine::Engine(){
        int flags = 0;
        if(m_fullscreen)flags=SDL_WINDOW_FULLSCREEN;
        if(SDL_Init(SDL_INIT_EVERYTHING)==0){
            std::cout<<"Subsystems Initialised!..."<<std::endl;
            m_window = SDL_CreateWindow("Platformer",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);
            if(m_window)std::cout<<"Window created!"<<std::endl;
            m_rendererSDL=SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(m_rendererSDL){
                SDL_SetRenderDrawColor(m_rendererSDL, 255, 255, 255, 255);
                std::cout<<"Renderer created!"<<std::endl;
            }
            m_status = Status::Ok;
        }
        else{
            m_status = Status::GLInitError;
        }
    }

    Engine::Status Engine::runClient(){

    }

    void Engine::handleInput(){
        mp_currentState->handleInput(m_keyboard, *m_window);
    }

    void Engine::update(){
        mp_currentState->update();
    }

    void Engine::render(){

    }

    void Engine::handleWindowEvents(){

    }

    void Engine::exit(){
        m_status = Status::Exit;
    }
}