//#include "SDL.h"
#include "game.hpp"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	const int fps = 60;
	const int frameDelay = 1000 / fps;

	Uint32 framestart;
	int frametime;

	game = new Game();

	game->init("Re-Collect", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, false);

	

	while (game->running()) {

		framestart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frametime = SDL_GetTicks() - framestart;

		if (frameDelay > frametime) {
			SDL_Delay(frameDelay - frametime);
		}

	}
	
	game->clean();

	return 0;
}