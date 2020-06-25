#include "renderer.h"

#include "../game/entity.h"

namespace client{
    Renderer::Renderer(){

    }
    
    void Renderer::process(const Entity &entity){
            m_entities.push_back(entity.pos);
    }

    void Renderer::render(SDL_Renderer &renderer){
        for(auto &batch : m_entities){
            SDL_Rect *temp;
            temp->x=batch.x;
            temp->y=batch.y;
            temp->w=40;
            temp->h=100;

            SDL_RenderFillRect(&renderer, temp);
        }
        m_entities.clear();
    }
}