#include "update.hpp"
#include "game.hpp"
#include <iostream>
#include <fstream>
#include "SDL.h"
#include "main.hpp"

int muurtop[2] = { 100, 100 };
int muurleft[2] = { 100, 300 };
int muurwidth[2] = { 100, 100 };
int muurheight[2] = { 100, 100 };

bool Update::playerCollision(gameObject* Object, gameObject* Map) {
	gameObject* object = Object;
	gameObject* map = Map;
	for (int i = 0; i < 2; i++) {

		int muur_top = muurtop[i] - map->srcy;
		int muur_bottom = muurtop[i] + muurheight[i] - map->srcy;
		int muur_left = muurleft[i] - map->srcx;
		int muur_right = muurleft[i] + muurwidth[i] - map->srcx;


		if (object->ypos > muur_bottom || object->xpos + 50 < muur_left || object->ypos + 50 < muur_top || object->xpos > muur_right) {
			//no collision
			
		}
		else {
			return true;
		}
	}
	return false;
}
int mapBorderx;
int mapBordery;
int mapsizex;
int mapsizey;


void Update::updateplayer(gameObject* Object, gameObject* Map, int border[2]) {

	gameObject* object = Object;
	gameObject* map = Map;

	std::ifstream mapSizeFile("maps/test/mapSize.txt");

	
	//save old position
	int xoud = object->xpos;
	int youd = object->ypos;
	int mapxoud = map->srcx;
	int mapyoud = map->srcy;
	
	while (mapSizeFile >> mapsizex >> mapsizey) {

		//std::cout << mapsizex << "\n" << mapsizey << std::endl;
		mapBorderx = mapsizex - 800;
		mapBordery = mapsizey - 600;

	}
	

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	//input checks
	if (keys[SDL_SCANCODE_A]) {
		if (object->xpos < 200 && map->srcx > -1) {			
			map->srcx--;	
		}
		else {
			object->xpos--;
		}
		
	}
	
	if (keys[SDL_SCANCODE_W]) {
		if (object->ypos < 150 && map->srcy > -1) {
			map->srcy--;

		}
		else {
			object->ypos--;
		}
	}
	
	if (keys[SDL_SCANCODE_S]) {
		if (object->ypos > 450 && map->srcy < mapBordery) {
			map->srcy++;
		}
		else {
			object->ypos++;
		}
	}
	
	if (keys[SDL_SCANCODE_D]) {
		if (object->xpos > 600 && map->srcx < mapBorderx) {	
			map->srcx++;		
		}
		else {
			object->xpos++;
		}
	}
	if (keys[SDL_SCANCODE_Q]) {
		Main master;
		master.changestate(0);
	}

	/*quit game, probably not needed and doesn't work
	
	if (keys[SDL_SCANCODE_LCTRL] && keys[SDL_SCANCODE_Q]) {
		
		std::cout << "quit game buttons pressed" << std::endl;
		//quit game
		Game game;
		game.isRunning = false;
	}*/
	
	//end of input checks

	//collision check

	if (Update::playerCollision(object, map)) {
		object->xpos = xoud;
		object->ypos = youd;
		map->srcx = mapxoud;
		map->srcy = mapyoud;
	}

	object->update();
	map->update();
	
}