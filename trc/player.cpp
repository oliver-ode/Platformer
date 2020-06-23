#include "player.hpp"


Player::Player(){}
Player::~Player(){}

void Player::init(int x, int y, int w, int h, SDL_Color c){
    xpos=x;
    ypos=y;
    width=w;
    height=h;
    color=c;
    player_rect.x=x;
    player_rect.y=y;
    player_rect.w=w;
    player_rect.h=h;

    initialized=true;
}

void Player::rectUpdate(){
    player_rect.x=xpos;
    player_rect.y=ypos;
    player_rect.w=width;
    player_rect.h=height;
}
void Player::updateVel(int velx, int vely){
    int vell[] = {velx, vely};
    if(vell[0]!=0){ //Movement in x direction
        if(vel[0]==0){ //Just one direction
            vel[0]=vell[0];
        }
        else{ //Trying both left and right
            vel[0]=0;
        }
    }
    else{ //Movement in y direction
        if(vel[1]==0){ //Just one direction
            vel[1]=vell[1];
        }
        else{ //Trying both up and down
            vel[1]=0;
        }
    }
}
void Player::calculateFinalVel(){ // Does stuff for diagonal
    if(vel[0] != 0 && vel[1] != 0){
        vel[0] *= velDiag;
        vel[1] *= velDiag;
    }
    else{
        vel[0] *= velReg;
        vel[1] *= velReg;
    }

}
void Player::move(){
    calculateFinalVel();
    std::cout<<"Vel[0]:"<<vel[0]<<", Vel[1]:"<<vel[1]<<std::endl;
    xpos+=vel[0];
    ypos+=vel[1];
    rectUpdate();
    vel[0]=0;
    vel[1]=0;
}