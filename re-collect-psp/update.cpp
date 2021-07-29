#include "update.hpp"
#include "game.hpp"
#include <iostream>
#include <fstream>
#include "glib2d.h"
#include "main.hpp"
#include <pspctrl.h>

int muurtop[2] = { 100, 100 };
int muurleft[2] = { 100, 300 };
int muurwidth[2] = { 100, 100 };
int muurheight[2] = { 100, 100 };

bool Update::playerCollision(gameObject* Object, gameObject* Map) {
	gameObject* object = Object;
	gameObject* map = Map;
	for (int i = 0; i < 2; i++) {

		int muur_top = muurtop[i] + map->ypos;
		int muur_bottom = muurtop[i] + muurheight[i] + map->ypos;
		int muur_left = muurleft[i] + map->xpos;
		int muur_right = muurleft[i] + muurwidth[i] + map->xpos;


		if (object->ypos > muur_bottom || object->xpos + 25 < muur_left || object->ypos + 25 < muur_top || object->xpos > muur_right) {
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


void Update::updateplayer(gameObject* Object, gameObject* Map) {
	
	SceCtrlData ctrldata;
	gameObject* object = Object;
	gameObject* map = Map;

	sceCtrlReadBufferPositive(&ctrldata, 1);

	std::ifstream mapSizeFile("maps/test/mapSize.txt");

	
	//save old position
	int xoud = object->xpos;
	int youd = object->ypos;
	int mapxoud = map->xpos;
	int mapyoud = map->ypos;
	
	while (mapSizeFile >> mapsizex >> mapsizey) {

		//std::cout << mapsizex << "\n" << mapsizey << std::endl;
		mapBorderx = mapsizex - 480 * -1;
		mapBordery = mapsizey - 272 * -1;

	}
	

	
	//input checks
	if (ctrldata.Buttons & PSP_CTRL_LEFT) {
		if (object->xpos < 40 && map->xpos < 0) {			
			map->xpos++;	
		}
		else {
			object->xpos--;
		}
		
	}
	
	if (ctrldata.Buttons & PSP_CTRL_UP) {
		if (object->ypos < 20 && map->ypos < 0) {
			map->ypos++;

		}
		else {
			object->ypos--;
		}
	}
	
	if (ctrldata.Buttons & PSP_CTRL_DOWN) {
		if (object->ypos > 252 && map->ypos > mapBordery) {
			map->ypos--;
		}
		else {
			object->ypos++;
		}
	}
	
	if (ctrldata.Buttons & PSP_CTRL_RIGHT) {
		if (object->xpos > 440 && map->srcx > mapBorderx) {	
			map->xpos--;		
		}
		else {
			object->xpos++;
		}
	}
	if (ctrldata.Buttons & PSP_CTRL_SELECT) {
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
		map->xpos = mapxoud;
		map->ypos = mapyoud;
	}

	object->update();
	map->update();
	
}