#include "game.hpp"
#include "TextureManager.hpp"
#include "gameObject.hpp"
#include "update.hpp"

gameObject* player;
//gameObject* player2;
Update updatefunction;

SDL_Renderer* Game::renderer = nullptr;



Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL initialized." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window) {
			std::cout << "window created." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "renderer created." << std::endl;
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}
	
	//debug rectangles to see test hitboxes
	r1.x = 100;
	r1.y = 100;
	r1.w = 100;
	r1.h = 100;

	r2.x = 300;
	r2.y = 100;
	r2.w = 100;
	r2.h = 100;
	

	player = new gameObject("assets/ricardo.png", 0, 0);
	//player2 = new gameObject("assets/ricardo.png", 75, 75);
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
		break;
	default:

	break;

	}
}

void Game::update() {
	
	updatefunction.updateplayer(player);
	
	//std::cout << "\nbuttons checked" << std::endl;
	//std::cout << "xpos: " << player->xpos << "\nypos: " << player->ypos << std::endl;
	//player->update();
	//player2->update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	//render stuff here
	player->render();

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &r1);
	SDL_RenderFillRect(renderer, &r2);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
	
	//player2->render();

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "quit game." << std::endl;
}
