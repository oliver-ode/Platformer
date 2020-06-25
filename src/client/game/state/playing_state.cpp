#include "playing_state.h"

// #include <glad/glad.h>
#include <iostream>

#include "../../input/keyboard.h"
#include "../../renderer/renderer.h"
#include "state_handler.h"

#include <SDL2/SDL.h>

namespace client{
    PlayingState::PlayingState(StateHandler &stateHandler) :GameState(stateHandler), m_client(m_entities){
        if(!m_client.connect(sf::IpAddress::LocalHost)){
            mp_stateHandler->popState();
        }
        for (auto &entity : m_entities){
            entity.alive = false;
        }
    }

    void PlayingState::handleKeyUp(int keyCode){
        
    }

    void PlayingState::handleInput(const Keyboard &keyboard, const SDL_Window &window){
        m_inputState = 0;
        if(keyboard.isKeyDown(SDLK_d)){
            m_inputState |= KeyInput::Right;
        }
        else if(keyboard.isKeyDown(SDLK_a)){
            m_inputState |= KeyInput::Left;
        }
        if(keyboard.isKeyDown(SDLK_w)){
            m_inputState |= KeyInput::Up;
        }
        else if(keyboard.isKeyDown(SDLK_s)){
            m_inputState |= KeyInput::Down;
        }

        m_client.sendInput(m_inputState);
    }

    void PlayingState::update(){
        m_client.update();
    }

    void PlayingState::render(Renderer &renderer){
        unsigned i = 0;
        for(const auto &e : m_entities){
            if(e.alive && i++ != m_client.getClientId()){
                renderer.process(e);
            }
        }
    }

    void PlayingState::onExit(){
        if(m_client.isConnected()){
            m_client.disconnect();
        }
    }

    Entity &PlayingState::getPlayerEntity(){
        return m_entities[m_client.getClientId()];
    }
}