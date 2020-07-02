#include "Game.hpp"

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
		isRunning = false;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Error initializing" << endl;
	}

	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (window) {
		cout << "Window created!" << endl;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 62, 65, 95, 255);
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	if (renderer) {
		cout << "Renderer created!" << endl;
	}
	isRunning = true;

	//Initialize stuff here
	playerInit();
	mapInit();
}

void Game::handleEvents() {
	SDL_Event event;
	const Uint8* keystate;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_a:
			a_pressed = true;
			break;
		case SDLK_d:
			d_pressed = true;
			break;
		case SDLK_w:
			w_pressed = true;
			break;
		case SDLK_s:
			s_pressed = true;
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_a:
			a_pressed = false;
			break;
		case SDLK_d:
			d_pressed = false;
			break;
		case SDLK_w:
			w_pressed = false;
			break;
		case SDLK_s:
			s_pressed = false;
			player.is_crouching = false;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	//Player movement
	player.xvel = 0;
	player.yvel = 0;

	if (w_pressed && !s_pressed)
		if (player.top_hit) player.yvel = 0;
		else {
			if (player.bottom_hit) {
				player.tick = 0;
				player.is_jumping = true;
			}
		}
	else if (s_pressed && !w_pressed)
		if (player.bottom_hit) player.is_crouching = true;
	if (a_pressed && !d_pressed)
		if (player.left_hit) player.xvel = 0;
		else player.xvel = -player.movement_speed;
	else if (d_pressed && !a_pressed)
		if (player.right_hit) player.xvel = 0;
		else player.xvel = player.movement_speed;
}

void Game::update() {

	player.update(renderer);

	player.movement_speed = 3;
	player.top_hit = false;
	player.bottom_hit = false;
	player.left_hit = false;
	player.right_hit = false;
	
	player.setHitbox(player.xpos + 27, player.ypos + 12, 23*2, 30*2);

	if (player.is_crouching) {
		player.movement_speed = 1;
		player.setHitbox(player.xpos + 30, player.ypos + 30, 20 * 2, 21 * 2);
	}
	if (player.is_dead) player.movement_speed = 0;

	updateCollision();
	
	// Here is my bad gravity physics
	if (player.is_jumping && !player.is_dead)
		if (player.top_hit || jump_ctr > player.jump_height) {
			player.is_jumping = false;
			player.is_falling = true;
			jump_ctr = 0;
		}
		else {
			player.ypos -= 5;
			jump_ctr += 3;
		}
	else if (!player.bottom_hit)
		player.ypos += 5;
}

void Game::render() {
	SDL_RenderClear(renderer);

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 27; j++) { 
			map[i][j].render(renderer, false);
		}
	}

	player.render(renderer, player.flip);
	//SDL_RenderFillRect(renderer, &player.getHitbox());

	SDL_RenderPresent(renderer);
}	

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game Destroyed" << endl;
}

void Game::playerInit() {
	string texfile;

	player.setSrc(0, 0, 50, 37);
	player.setDest(130, 500, 2);
	player.movement_speed = 3;

	for (int i = 0; i < 4; i++) {
		texfile = "assets/player/adventurer-idle-2-0" + to_string(i) + ".png";
		player.add_texture(texfile, 0);
	}
	for (int i = 0; i < 6; i++) {
		texfile = "assets/player/adventurer-run-0" + to_string(i) + ".png";
		player.add_texture(texfile, 1);
	}
	for (int i = 0; i < 3; i++) {
		texfile = "assets/player/adventurer-jump-0" + to_string(i) + ".png";
		player.add_texture(texfile, 2);
	}
	for (int i = 0; i < 2; i++) {
		texfile = "assets/player/adventurer-fall-0" + to_string(i) + ".png";
		player.add_texture(texfile, 3);
	}
	for (int i = 0; i < 4; i++) {
		texfile = "assets/player/adventurer-crouch-0" + to_string(i) + ".png";
		player.add_texture(texfile, 4);
	}
	for (int i = 0; i < 7; i++) {
		texfile = "assets/player/adventurer-die-0" + to_string(i) + ".png";
		player.add_texture(texfile, 5);
	}
}

void Game::mapInit() {
	for (int i = 0; i < 6; i++) {
		string tilefile = "assets/tileset/tile0" + to_string(i) + ".png";
		tiles.push_back(tilefile);
	}
	
	ifstream map_file("assets/tileset/map1.map");
	if (!map_file) {
		cout << "Unable to open file" << endl;
	}

	string line, c;
	int col, row = 0;
	GameObject* tile;
	while (getline(map_file, line)) {
		col = 0;
		for (int i = 0; i < 27*2-1; i++) {
			c = line[i];
			if (strcmp(c.c_str(), " ") != 0) {
				tile = &map[row][col];
				tile->setSrc(0, 0, 16, 16);
				tile->setDest(col * 48, row * 48, 3);
				switch (stoi(c)) {
				case 0:
					tile->setTexture(tiles.at(rand() % 2).c_str(), renderer);
					break;
				case 2:
					tile->setTexture(tiles.at(2).c_str(), renderer);
					tile->setHitbox(tile->getDest().x, tile->getDest().y, tile->getDest().w, tile->getDest().h);
					tile->isSolid = true;
					break;
				case 3:
					tile->setTexture(tiles.at(3).c_str(), renderer);
					tile->setHitbox(tile->getDest().x, tile->getDest().y, tile->getDest().w, 21);
					tile->isSolid = true;
					break;
				case 4:
					tile->setTexture(tiles.at(4).c_str(), renderer);
					tile->setHitbox(tile->getDest().x, tile->getDest().y + 24, tile->getDest().w, 24);
					tile->isSolid = true;
					tile->isTrap = true;
					break;
				case 5:
					tile->setTexture(tiles.at(5).c_str(), renderer);
					tile->setHitbox(tile->getDest().x, tile->getDest().y, tile->getDest().w, tile->getDest().h);
					tile->isSolid = true;
					tile->isTrap = true;
					break;
				default:
					break;
				}
				col++;
			}
		}
		row++;
	}
	map_file.close();
}

void Game::checkCollision(Entity entity, GameObject tile) {
	int ent_x = entity.getHitbox().x;
	int ent_y = entity.getHitbox().y;
	int ent_w = entity.getHitbox().w;
	int ent_h = entity.getHitbox().h;
	int tile_x = tile.getHitbox().x;
	int tile_y = tile.getHitbox().y;
	int tile_w = tile.getHitbox().w;
	int tile_h = tile.getHitbox().h;

	bool in_xrange = ent_x+ent_w-5 >= tile_x && ent_x+5 <= tile_x + tile_w;
	bool in_yrange = ent_y+ent_h-5 >= tile_y && ent_y+5 <= tile_y + tile_h;

	if ((ent_y + ent_h) >= tile_y && ent_y < tile_y && in_xrange) {
		//cout << "bottom hit" << endl;
		player.bottom_hit = true;
	}
	else if (ent_y <= (tile_y + tile_h) && (ent_y + ent_h) > (tile_y + tile_h) && in_xrange) {
		//cout << "top hit" << endl;
		player.top_hit = true;
	}
	if ((ent_x + ent_w) >= tile_x && ent_x < tile_x && in_yrange) {
		//cout << "right hit" << endl;
		player.right_hit = true;
	}
	else if (ent_x <= (tile_x + tile_w) && (ent_x + ent_w) > (tile_x + tile_w) && in_yrange) {
		//cout << "left hit" << endl;
		player.left_hit = true;
	}

	if (tile.isTrap) {
		player.is_dead = true;
	}
}

void Game::updateCollision() {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 27; j++) {
			if (player.collision(map[i][j])) {
				checkCollision(player, map[i][j]);
			}
		}
	}
}