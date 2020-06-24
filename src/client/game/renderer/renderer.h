#pragma once

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

            void render();
    };
}