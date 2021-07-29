//#include "SDL.h"
#include "game.hpp"
#include "main.hpp"
#include "menu.hpp"


Game* game = nullptr;
int state = 0;


int main(int argc, char* argv[]) {
	
	//Main master;
	const int fps = 60;
	const int frameDelay = 1000 / fps;

	

	Uint32 framestart;
	int frametime;

	game = new Game();
	Menu menu;
	
	
	
	
	game->init("Re-Collect", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	
	if (!menu.initMenu()) {
		game->isRunning = false;
	}
	/*gamestates:
	0: main menu
	1: main game
	*/

	while (game->running()) {
		
		framestart = SDL_GetTicks();

		if (state == 0) {
			game->handleEvents();
			menu.updateMenu();
			menu.renderMenu();
		}

		if (state == 1) {
			game->handleEvents();
			game->update();
			game->render();
		}
		if (state < 0 || state > 1) {
			std::cout << "non existent game state set.\ngame state value is: " << state << std::endl;
			game->isRunning = false;
		}

		frametime = SDL_GetTicks() - framestart;

		if (frameDelay > frametime) {
			SDL_Delay(frameDelay - frametime);
		}

	}
	
	game->clean();
	SDL_Delay(3000);
	std::cout << "quitting game";
	return 0;
}
void Main::changestate(int newState) {
	state = newState;
	std::cout << "changed gamestate to: " << state << std::endl;
}