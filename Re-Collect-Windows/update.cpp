#include "update.hpp"
#include "game.hpp"
#include <iostream>
#include <fstream>
#include "SDL.h"
#include "main.hpp"
#include "SDL_ttf.h"
#include "textureManager.hpp"
#include <string>

TextureManager text;

int mapBorderx;
int mapBordery;
int mapsizex;
int mapsizey;
bool pressed = false;
const char* messagechar;
SDL_Color black = { 0,0,0 };
SDL_Color white = { 255,255,255 };


//wall hitboxes
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
int interactTop[2] = { 500, 300 };
int interactLeft[2] = { 100, 800 };
int interactWidth[2] = { 50, 50 };
int interactHeight[2] = { 50, 50 };

int Update::ableToInteract(gameObject* Object, gameObject* Map) {
	gameObject* object = Object;
	gameObject* map = Map;
	for (int i = 0; i < 2; i++) {

		int interact_top = interactTop[i] - map->srcy;
		int interact_bottom = interactTop[i] + interactHeight[i] - map->srcy;
		int interact_left = interactLeft[i] - map->srcx;
		int interact_right = interactLeft[i] + interactWidth[i] - map->srcx;


		if (object->ypos > interact_bottom || object->xpos + 50 < interact_left || object->ypos + 50 < interact_top || object->xpos > interact_right) {
			//no collision

		}
		else {
			//i + 1 because 0 is not able to interact but th first one iin the array is also 0
			return i + 1;
		}
	}
	return 0;
}


void Update::updateplayer(gameObject* Object, gameObject* Map) {

	gameObject* object = Object;
	gameObject* map = Map;
	Game game;
	//TextureManager texture;
	std::ifstream mapSizeFile("maps/test/mapSize.txt");
	
	
	//save old position
	int xoud = object->xpos;
	int youd = object->ypos;
	int mapxoud = map->srcx;
	int mapyoud = map->srcy;
	
	while (mapSizeFile >> mapsizex >> mapsizey) {

		//std::cout << mapsizex << "\n" << mapsizey << std::endl;
		mapBorderx = mapsizex - game.screenWidth;
		mapBordery = mapsizey - game.screenHeight;

	}
	

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	interactState = ableToInteract(object, map);
	//input checks
	if (!interacting) {
		if (interactState == 0) {
			//not able to interact
		}
		else {
			//std::cout << "able to interact with interactable: " << interactState << std::endl;
			if (keys[SDL_SCANCODE_E]) {
				std::cout << "starting interaction with " << interactState << std::endl;
				
				interacting = true;
			}
		}

		if (keys[SDL_SCANCODE_A]) {
			if (object->xpos < 200 && map->srcx > -1) {
				if (keys[SDL_SCANCODE_LSHIFT]) {
					map->srcx -= 2;
				}
				else {
					map->srcx--;
				}
			}
			else {
				if (keys[SDL_SCANCODE_LSHIFT]) {
					object->xpos -= 2;
				}
				else {
					object->xpos--;
				}
			}

		}

		if (keys[SDL_SCANCODE_W]) {
			if (object->ypos < 150 && map->srcy > -1) {
				if (keys[SDL_SCANCODE_LSHIFT]) {
					map->srcy -= 2;
				}
				else {
					map->srcy--;
				}


			}
			else {
				if (keys[SDL_SCANCODE_LSHIFT]) {
					object->ypos -= 2;
				}
				else {
					object->ypos--;
				}

			}
		}

		if (keys[SDL_SCANCODE_S]) {
			if (object->ypos > map->sizeh - 150 && map->srcy < mapBordery) {
				if (keys[SDL_SCANCODE_LSHIFT]) {
					map->srcy += 2;
				}
				else {
					map->srcy++;
				}

			}
			else {
				if (keys[SDL_SCANCODE_LSHIFT]) {
					object->ypos += 2;
				}
				else {
					object->ypos++;
				}

			}
		}

		if (keys[SDL_SCANCODE_D]) {
			if (object->xpos > map->sizew - 200 && map->srcx < mapBorderx) {
				if (keys[SDL_SCANCODE_LSHIFT]) {
					map->srcx += 2;
				}
				else {
					map->srcx++;
				}

			}
			else {
				if (keys[SDL_SCANCODE_LSHIFT]) {
					object->xpos += 2;
				}
				else {
					object->xpos++;
				}

			}
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
	}
	else {
		
		
	}
	if (keys[SDL_SCANCODE_Q]) {
		Main master;
		master.changestate(0);
	}
	object->update();
	map->update();
	
}

void Update::renderText(TTF_Font* font, int screenwidth, int screenheight) {
	//rendering text
	

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	//interacting with something 
	if (interactState == 1) {
		switch (message) {
		case 0:
			text.loadFont("test message 1", font, black, 100, screenheight - 150);
			if (keys[SDL_SCANCODE_SPACE] && pressed == false) {
				pressed = true;
				message++;
				std::cout << "now displaying interaction " << interactState << " message " << message << ".\n";
			}
			else if (!keys[SDL_SCANCODE_SPACE]) {
				pressed = false;
			}
			else {

			}
			break;

		case 1:
			text.loadFont("test message 2!", font, black, 100, screenheight - 150);
			if (keys[SDL_SCANCODE_SPACE] && pressed == false) {
				pressed = true;
				message++;
				std::cout << "now displaying interaction " << interactState << " message " << message << ".\n";
			}
			else if (!keys[SDL_SCANCODE_SPACE]) {
				pressed = false;
			}
			else {

			}
			break;

		case 2:
			interacting = false;
			message = 0;
			break;
		}

	}
	else if (interactState == 2) {
		switch (message) {
		case 0:
			text.loadFont("hi!", font, black, 100, screenheight - 150);
			if (keys[SDL_SCANCODE_SPACE] && pressed == false) {
				pressed = true;
				message++;
				std::cout << "now displaying interaction " << interactState << " message " << message << ".\n";
			}
			else if (!keys[SDL_SCANCODE_SPACE]) {
				pressed = false;
			}
			else {

			}
			break;

		case 1:
			text.loadFont("me is chad!", font, black, 100, screenheight - 150);
			if (keys[SDL_SCANCODE_SPACE] && pressed == false) {
				pressed = true;
				message++;
				std::cout << "now displaying interaction " << interactState << " message " << message << ".\n";

			}
			else if (!keys[SDL_SCANCODE_SPACE]) {
				pressed = false;
			}
			else {

			}
			break;

		case 2:
			interacting = false;
			message = 0;
			break;
		}
	}

	else {

		switch (message) {
		case 0:
			text.loadFont("sorry, nobody programmed a response for me!", font, black, 100, screenheight - 150);
			if (keys[SDL_SCANCODE_SPACE] && pressed == false) {
				pressed = true;
				message++;
				std::cout << "now displaying interaction " << interactState << " message " << message << ".\n";
			}
			else if (!keys[SDL_SCANCODE_SPACE]) {
				pressed = false;
			}
			else {

			}


			break;
		case 1:
			text.loadFont("this shouldn't happen, contact the developer about this.", font, black, 100, screenheight - 150);
			if (keys[SDL_SCANCODE_SPACE] && pressed == false) {
				pressed = true;
				message++;
				std::cout << "now displaying interaction " << interactState << " message " << message << ".\n";
			}
			else if (!keys[SDL_SCANCODE_SPACE]) {
				pressed = false;
			}
			else {

			}
			break;
		case 2:

			//messagechar = ("oh, and tell him that my id is " + std::to_string(updatefunction.interactState)).c_str();
			text.loadFont(("oh, and tell him that my id is " + std::to_string(interactState)).c_str(), font, { 0,0,0 }, 100, screenheight - 150);

			if (keys[SDL_SCANCODE_SPACE] && pressed == false) {
				pressed = true;
				message++;
				std::cout << "now displaying interaction " << interactState << " message " << message << ".\n";
			}
			else if (!keys[SDL_SCANCODE_SPACE]) {
				pressed = false;
			}
			else {

			}
			break;

		case 3:
			interacting = false;
			message = 0;
			break;
		}



	}
}