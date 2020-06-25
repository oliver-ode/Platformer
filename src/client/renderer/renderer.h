#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

namespace client{
    class Entity;

    class Renderer final{
        public:
            Renderer();
            ~Renderer() = default;

            Renderer(Renderer &&) = delete;
            Renderer &operator=(Renderer &&) = delete;

            Renderer(const Renderer &) = delete;
            Renderer &operator=(const Renderer &) = delete;

            void process(const Entity &entity);

            void render(SDL_Renderer &renderer);
        private:
            std::vector<glm::vec2> m_entities;
    };
}