#ifndef Game_hpp
#define Game_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "GameObject.hpp"
#include "Entity.hpp"

using namespace std;

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }

	void playerInit();
	void mapInit();
	
	void updateCollision();
	void checkCollision(Entity entity, GameObject tile);

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	vector<string> tiles;
	GameObject map[15][27];
	Entity player;

	bool w_pressed;
	bool a_pressed;
	bool s_pressed;
	bool d_pressed;

	int jump_ctr = 0;
};

#endif // !Game_hpp