#include "Entity.hpp"
#include <cmath>


string tex;
bool bruh = false;

void Entity::add_texture(string animation, int type) {
	switch (type) {
	case 0:
		idle.push_back(animation);
		break;
	case 1:
		run.push_back(animation);
		break;
	case 2:
		jumper.push_back(animation);
		break;
	case 3:
		faller.push_back(animation);
		break;
	case 4:
		crouch.push_back(animation);
		break;
	case 5:
		die.push_back(animation);
		break;
	default:
		break;
	}
}

void Entity::update(SDL_Renderer* ren) {
	tick++;

	if (xvel > 0) flip = false;
	else if (xvel < 0) flip = true;

	if (xvel == 0 && yvel == 0 && !is_jumping && !is_falling && !is_crouching && !is_dead) {
		if (tick > pow(3, 3)) tick = 0;
		setTexture(idle.at(tick / pow(3, 2)).c_str(), ren);
	}
	else if (is_dead) {
		if (tick > pow(6, 2)) tick = 0;
		tex = die.at(tick / pow(6, 1));
		setTexture(die.at(tick / pow(6, 1)).c_str(), ren);
		if (tex == die.back()) {
			setPos(130, 500);
			is_dead = false;
		}
	}
	else if (is_jumping) {
		//cout << bottom_hit << endl;
		setTexture(jumper.back().c_str(), ren);
	}
	else if (is_falling) {
		if (tick > pow(1, 3)) tick = 0;
		setTexture(faller.at(tick / pow(1, 2)).c_str(), ren);
		if (bottom_hit)
			is_falling = false;
	}
	else if (is_crouching) {
		if (tick > pow(3, 3)) tick = 0;
		setTexture(crouch.at(tick / pow(3, 2)).c_str(), ren);
	}
	else {
		if (tick > pow(5, 2)) tick = 0;
		setTexture(run.at(tick / pow(5, 1)).c_str(), ren);
	}
	
	setPos(xpos + xvel, ypos + yvel);
}

bool Entity::collision(GameObject rect) {
	int x_center = xpos + getDest().w / 2;
	if (
		getHitbox().x + getHitbox().w >= rect.getHitbox().x &&
		rect.getHitbox().x + rect.getHitbox().w >= getHitbox().x &&
		getHitbox().y + getHitbox().h >= rect.getHitbox().y &&
		rect.getHitbox().y + rect.getHitbox().h >= getHitbox().y &&
		rect.isSolid
		) 
		return true;
	else return false;
}
