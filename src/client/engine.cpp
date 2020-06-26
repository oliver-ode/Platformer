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
        m_fpsCounter.reset();
        int frame = 0;
        while(m_status==Status::Ok){
            mp_currentState = &m_stateHandler.peekState();

            handleWindowEvents();
            handleInput();
            update();
            render();

            m_fpsCounter.update();

            if(frame++ == 512){
                std::cout<<"Frame Time: "<<m_fpsCounter.currentMsPerFrame()<<" ms"<<'\n'<<std::endl;
                frame = 0;
            }

            m_stateHandler.update();
            if(m_stateHandler.isEmpty()){
                exit();
            }
        }
        m_stateHandler.clear();

        return m_status;
    }

    void Engine::handleInput(){
        mp_currentState->handleInput(m_keyboard, *m_window);
    }

    void Engine::update(){
        mp_currentState->update();
    }

    void Engine::render(){
        SDL_SetRenderDrawColor(m_rendererSDL, 255, 255, 255, 255);
        SDL_RenderClear(m_rendererSDL);

        mp_currentState->render(*m_renderer);

        SDL_RenderPresent(m_rendererSDL);
    }

    void Engine::handleWindowEvents(){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            m_keyboard.update(e);
            switch(e.type){
                case SDL_KEYDOWN:
                    mp_currentState->handleKeyDown(e.key.keysym.sym);
                    switch(e.key.keysym.sym){
                        case SDLK_ESCAPE:
                            exit();
                            break;
                        default:
                            break;
                    }
                case SDL_KEYUP:
                    mp_currentState->handleKeyUp(e.key.keysym.sym);
                    break;
                case SDL_QUIT:
                    exit();
                    break;
                default:
                    break;
            }
        }
    }

    void Engine::exit(){
        m_status = Status::Exit;
    }
}