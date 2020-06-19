#include "event_handler.hpp"

EventHandler::EventHandler(){};
EventHandler::~EventHandler(){};

int EventHandler::handleEvent(SDL_Event event){
    switch(event.type){
        case SDL_QUIT:
            return(-1); //Treat -1 as game quit
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_ESCAPE:
                    return(-1);
                default:
                    //std::cout<<"Key pressed: "<<event.key.keysym.sym<<std::endl;
                    if(event.key.keysym.sym<keySize){
                        keyState[event.key.keysym.sym]=true;
                        return(1); //Processed
                    }
                    return(-2); //Weird key code
            }
        case SDL_KEYUP:
            if(event.key.keysym.sym<keySize){
                keyState[event.key.keysym.sym]=false;
                return(1); //Processed
            }
            return(-2); //Weird key code
    }
    return(0); //Nothing processed
}
bool EventHandler::keyPressed(int keyCode){
    return(keyState[keyCode]==true);
}
bool EventHandler::keyReleased(int keyCode){
    return(keyState[keyCode]==false);
}
bool EventHandler::keyPairPressed(int keyCode1, int keyCode2){
    return(keyState[keyCode1]==true&&keyState[keyCode2]==true);
}