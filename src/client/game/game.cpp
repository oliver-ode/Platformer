#include "game.hpp"

Game::Game(){}
Game::~Game(){}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen)flags=SDL_WINDOW_FULLSCREEN;
    if(SDL_Init(SDL_INIT_EVERYTHING)==0){
        std::cout<<"Subsystems Initialised!..."<<std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window)std::cout<<"Window created!"<<std::endl;
        renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout<<"Renderer created!"<<std::endl;
        }
        isRunning=true;
    }
    else{
        isRunning=false;
    }
}
// Input is handled
void Game::handleEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(evh->handleEvent(event) == -1){
            isRunning=false;
        }
    }
    
}
// Any updates to values and such
void Game::update(){
    // Player movement
    if(evh->keyPressed(SDLK_d)){
        player->updateVel(1, 0);
        playerMove=true;
    }
    if(evh->keyPressed(SDLK_a)){
        player->updateVel(-1, 0);
        playerMove=true;
    }
    if(evh->keyPressed(SDLK_s)){
        player->updateVel(0, 1);
        playerMove=true;
    }
    if(evh->keyPressed(SDLK_w)){
        player->updateVel(0, -1);
        playerMove=true;
    }
    if(playerMove){
        player->move();
        std::cout<<player->getXpos()<<" : "<<player->getYpos()<<std::endl;
        playerMove=false;
    }
}
// Anything that needs to get rendered
void Game::render(){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    // Player rendering
    if(player->initialized){
        SDL_SetRenderDrawColor(renderer, player->getColor().r, player->getColor().g, player->getColor().b, player->getColor().a);
        SDL_RenderFillRect(renderer, player->getRect());
    }

    SDL_RenderPresent(renderer);
}
// Cleans up the game when we want to quit it
void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout<<"Game Cleaned"<<std::endl;
}

void Game::createPlayer(int xpos, int ypos, int width, int height, SDL_Color color){
    player->init(xpos, ypos, width, height, color);
}