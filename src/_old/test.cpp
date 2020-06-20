#include <iostream>

#include "../deps/glad/glad.h"
#include <SDL2/SDL.h>

const int WIDTH = 1920, HEIGHT = 1080;

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL2 video subsystem couldn't be initialized. Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_Window* window = SDL_CreateWindow("Glad Sample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) {
        std::cerr << "SDL2 Renderer couldn't be created. Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create a OpenGL context on SDL2
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    // Load GL extensions using glad
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize the OpenGL context." << std::endl;
        exit(1);
    }

    // Loaded OpenGL successfully.
    std::cout << "OpenGL version loaded: " << GLVersion.major << "." << GLVersion.minor << std::endl;

    // Create an event handler
    SDL_Event event;
    // Loop condition
    bool running = true;

    int mid[2] = {WIDTH/2, 0};
    int left[2] = {0, HEIGHT-1};
    int right[2] = {WIDTH-1, HEIGHT-1};

    int cur = 0;
    int prev = 0;

    while (running) {
        SDL_PollEvent(&event);

        prev = cur;
        cur = SDL_GetTicks();
        std::cout<<cur-prev<<std::endl;

        switch(event.type) {
        case SDL_QUIT:
            running = false;
            break;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
            case SDLK_ESCAPE:
                running = false;
                break;
            case SDLK_w:
                mid[1]--;
                left[1]--;
                right[1]--;
                break;
            case SDLK_s:
                mid[1]++;
                left[1]++;
                right[1]++;
                break;
            case SDLK_a:
                mid[0]--;
                left[0]--;
                right[0]--;
                break;
            case SDLK_d:
                mid[0]++;
                left[0]++;
                right[0]++;
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        //Drawing the lines we want. (-1, 0), (0, 1), (1, 0)
        SDL_RenderDrawLine(renderer, left[0], left[1], mid[0], mid[1]);
        SDL_RenderDrawLine(renderer, left[0], left[1], right[0], right[1]);
        SDL_RenderDrawLine(renderer, mid[0], mid[1], right[0], right[1]);

        //Update the Renderer.
        SDL_RenderPresent(renderer);

        SDL_GL_SwapWindow(window);
    }

    // Destroy everything to not leak memory.
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
