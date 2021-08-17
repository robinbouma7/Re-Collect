#define _CRT_SECURE_NO_WARNINGS
//#include "SDL.h"
#include "game.hpp"
#include "main.hpp"
#include "menu.hpp"
#include <iostream>
#include "discord_rpc.h"


Game* game = nullptr;
int state = 0;
int frame = 0;


int SDL_main(int argc, char* argv[]) {
	
	//Main master;
	game = new Game();
	

	
	const int fps = 60;
	const int frameDelay = 1000 / fps;

	

	Uint32 framestart;
	int frametime;

	
	Menu menu;
	
	
	
	
	if (game->init("Re-Collect", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, false) == 1) {
		std::cout << "game initialised" << std::endl;
		//std::cout << "renderer size check in main: \nwidth: " << game->screenWidth << "\nheight: " << game->screenHeight << std::endl;

		if (menu.initMenu(game->screenWidth, game->screenHeight)) {
			std::cout << "menu initialised" << std::endl;

		}
		else {
			game->isRunning = false;
		}
	}
	else {
		game->isRunning = false;
	}
	game->InitDiscord();
	
	/*gamestates:
	0: main menu
	1: main game
	*/

	while (game->running()) {
		frame++;
		framestart = SDL_GetTicks();
		

		
		if (state == 0) {
			game->handleEvents();
			menu.updateMenu();
			menu.renderMenu();
			game->UpdatePresence("in menu.");
		}

		if (state == 1) {
			game->handleEvents();
			game->update();
			game->render();
			game->UpdatePresence("in game.");
		}
		if (frame == 59) {

			frame = 0;

			if (state == 0) {
				game->UpdatePresence("in menu.");
			}

			else if (state == 1) {
				game->UpdatePresence("in game");
			}

			else {
				game->UpdatePresence("gaming");
			}	
		}
		if (state < 0 || state > 1) {
			std::cout << "non existent game state set.\ngame state value is: " << state << std::endl;
			game->isRunning = false;
		}
		Discord_RunCallbacks();
		frametime = SDL_GetTicks() - framestart;

		if (frameDelay > frametime) {
			SDL_Delay(frameDelay - frametime);
		}

	}
	std::cout << std::endl << SDL_GetError() << std::endl;
	game->clean();
	std::cout << std::endl << SDL_GetError() << std::endl;
	Discord_RunCallbacks();
	Discord_Shutdown();
	SDL_Delay(3000);
	std::cout << "quitting game";
	return 0;
}
void Main::changestate(int newState) {
	state = newState;
	std::cout << "changed gamestate to: " << state << std::endl;
}