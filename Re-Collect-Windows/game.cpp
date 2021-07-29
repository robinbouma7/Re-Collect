#include "game.hpp"
#include "TextureManager.hpp"
#include "gameObject.hpp"
#include "update.hpp"
#include "main.hpp"

gameObject* player;
gameObject* map;
//gameObject* player2;
Update updatefunction;

SDL_Renderer* Game::renderer = nullptr;

int menu = 0;

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	std::cout << "als het spel opent druk op enter om te starten.\ndeze console is voor testen en gaat in en latere versie weg.\nals je een probleem heb zeg het me maar.\n\nen trouwens, collision is er alleen op 2 100 bij 100 px vierkanten.\ndeze zijn op x:100 y:100 en x:300 y:100.\n\nde grootte van het scherm word nog veranderd." << std::endl;

	int flags = 0;

	Game::cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	SDL_SetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION, "1");
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL initialized." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window) {
			std::cout << "window created." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
	
	r1.w = 100;
	r1.h = 100;

	
	r2.w = 100;
	r2.h = 100;
	
	//path, x, y, srcx, srcy, srcw, srch
	player = new gameObject("assets/ricardo.png", 375, 275, 0, 0, 25, 25);
	map = new gameObject("maps/test/testMap.png", 0, 0, 0, 0, 800, 600);

	player->sizeh = 50;
	player->sizew = 50;
	map->sizeh = 600;
	map->sizew = 800;
	
	
	//player2 = new gameObject("assets/ricardo.png", 75, 75);
}

void Game::handleEvents() {
	
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
		break;
	default:

	break;

	}
}
int testMap[2]{ 1200, 900 };
void Game::update() {
	
	updatefunction.updateplayer(player, map, testMap);

	r1.x = 100 - map->srcx;
	r1.y = 100 - map->srcy;

	r2.x = 300 - map->srcx;
	r2.y = 100 - map->srcy;
	
	//std::cout << "\nbuttons checked" << std::endl;
	//std::cout << "xpos: " << player->xpos << "\nypos: " << player->ypos << std::endl;
	//player->update();
	//player2->update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	//render stuff here
	map->render();
	player->render();
	//rectangles used for tessting hitboxes.
	//std::cout << "x: " << player->xpos << "\ny: " << player->ypos << std::endl;
	//SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	//SDL_RenderFillRect(renderer, &r1);
	//SDL_RenderFillRect(renderer, &r2);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
	
	//player2->render();

	SDL_SetCursor(Game::cursor);
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "window closed." << std::endl;
}
