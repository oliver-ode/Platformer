#ifndef Entity_hpp
#define Entity_hpp

#include "GameObject.hpp"
#include <vector>
#include <string>

using namespace std;


class Entity : public GameObject {
public:
	void add_texture(string animation, int type);
	void update(SDL_Renderer* ren);	
	bool collision(GameObject rect);

	int tick = 0;
	int movement_speed;
	int jump_height = 35;

	bool flip;
	bool top_hit;
	bool bottom_hit;
	bool left_hit;
	bool right_hit;

	bool is_jumping = false;
	bool is_falling = false;
	bool is_crouching = false;
	bool is_dead = false;

private:
	vector<string> idle;
	vector<string> run;
	vector<string> jumper;
	vector<string> faller;
	vector<string> crouch;
	vector<string> die;
};

#endif // !Entity_hpp
