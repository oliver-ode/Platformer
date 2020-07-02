#include <SDL2/SDL.h>
#include "Game.hpp"


int main(int argc, char* argv[]) {
	Game *game = new Game();

	//Variables to cap framerate
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart = 0;
	int frameTime;

	game->init("My SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1296, 720, false);

	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		//Add additional delay if computer fps too fast
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}