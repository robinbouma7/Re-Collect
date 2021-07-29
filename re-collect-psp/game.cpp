#include "game.hpp"
#include "TextureManager.hpp"
#include "gameObject.hpp"
#include "update.hpp"
#include "main.hpp"
#include "glib2d.h"

gameObject* player;
gameObject* map;
//gameObject* player2;
Update updatefunction;

//SDL_Renderer* Game::renderer = nullptr;

int menu = 0;

Game::Game() {

}
Game::~Game() {

}

void Game::init() {
	//std::cout << "als het spel opent druk op enter om te starten.\ndeze console is voor testen en gaat in en latere versie weg.\nals je een probleem heb zeg het me maar.\n\nen trouwens, collision is er alleen op 2 100 bij 100 px vierkanten.\ndeze zijn op x:100 y:100 en x:300 y:100.\n\nde grootte van het scherm word nog veranderd." << std::endl;

	isRunning = true;

	//debug rectangles to see test hitboxes
	
	//r1.w = 100;
	//r1.h = 100;

	
	//r2.w = 100;
	//r2.h = 100;
	
	//path, x, y, srcx, srcy, srcw, srch
	player = new gameObject("assets/ricardo.png", 228, 124, 25, 25);
	map = new gameObject("maps/test/testMap.png", 0, 0, 2000, 1500);

	//player->sizeh = 50;
	//player->sizew = 50;
	//map->sizeh = 600;
	//map->sizew = 800;
	
	
	//player2 = new gameObject("assets/ricardo.png", 75, 75);
}

void Game::handleEvents() {
	
}
//int testMap[2]{ 1200, 900 };
void Game::update() {
	
	updatefunction.updateplayer(player, map);

	//r1.x = 100 - map->srcx;
	//r1.y = 100 - map->srcy;

	//r2.x = 300 - map->srcx;
	//r2.y = 100 - map->srcy;
	
	//std::cout << "\nbuttons checked" << std::endl;
	//std::cout << "xpos: " << player->xpos << "\nypos: " << player->ypos << std::endl;
	//player->update();
	//player2->update();
}

void Game::render() {
	g2dClear(BLACK);
	//render stuff here

	map->render();
	player->render();

	//rectangles used for tessting hitboxes.
	//std::cout << "x: " << player->xpos << "\ny: " << player->ypos << std::endl;

	g2dFlip(G2D_VSYNC);
}
