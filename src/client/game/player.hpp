#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>
#include <iostream>

class Player{
    public:
        bool initialized;

        Player();
        ~Player();

        void init(int xpos, int ypos, int width, int height, SDL_Color color);

        // Getters
        int getXpos(){return(xpos);}
        int getYpos(){return(ypos);}
        int getWidth(){return(width);}
        int getHeight(){return(height);}
        SDL_Color getColor(){return(color);}
        SDL_Rect* getRect(){return(&player_rect);}
        
        // Reworked movement
        void updateVel(int velx, int vely);
        void calculateFinalVel();
        void move();

        void rectUpdate();
    private:
        int xpos;
        int ypos;
        int width; //Can be removed later
        int height; //Can be removed later
        SDL_Color color;
        SDL_Rect player_rect;

        int vel[2] = {0, 0};
        int velReg = 4;
        int velDiag = 3; //Lower velocity for moving in multiple directions at once
};

#endif