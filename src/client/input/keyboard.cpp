#include <keyboard.h>

namespace client{
    Keyboard::Keyboard(){
        std::fill(m_keys.begin(), m_keys.end(), false);
    }

    void Keyboard::update(SDL_Event e){
        m_recentlyReleased = -1;
        switch(e.type){
            case SDL_KEYUP:
                if(e.key.keysym.sym<keySize){
                    m_recentlyReleased = e.key.keysym.sym;
                    m_keys[e.key.keysym.sym] = false;
                    break;
                }
            case SDL_KEYDOWN:
                if(e.key.keysym.sym<keySize){
                    m_keys[e.key.keysym.sym] = true;
                    break;
                }
            default:
                break;
        }
    }
    bool Keyboard::isKeyDown(int keyCode){
        return m_keys[keyCode];
    }
    bool Keyboard::isKeyReleased(int keyCode){
        return m_recentlyReleased == keyCode;
    }
    void Keyboard::resetKeys(){
        std::fill(m_keys.begin(), m_keys.end(), false);
    }
}