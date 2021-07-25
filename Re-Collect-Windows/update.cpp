#include "update.hpp"
#include "game.hpp"
#include <iostream>
#include "SDL.h"

int muurtop[2] = { 100, 100 };
int muurleft[2] = { 100, 300 };
int muurwidth[2] = { 100, 100 };
int muurheight[2] = { 100, 100 };

bool Update::playerCollision(gameObject* Object) {
	gameObject* object = Object;

	for (int i = 0; i < 2; i++) {

		int muur_top = muurtop[i];
		int muur_bottom = muurtop[i] + muurheight[i];
		int muur_left = muurleft[i];
		int muur_right = muurleft[i] + muurwidth[i];


		if (object->ypos > muur_bottom || object->xpos + 50 < muur_left || object->ypos + 50 < muur_top || object->xpos > muur_right) {
			//no collision
			
		}
		else {
			return true;
			std::cout << "collision resolved!" << std::endl;
		}
	}
	return false;
}

void Update::updateplayer(gameObject* Object) {

	gameObject* object = Object;

	//save old position
	int xoud = object->xpos;
	int youd = object->ypos;


	const Uint8* keys = SDL_GetKeyboardState(NULL);
	//input checks
	if (keys[SDL_SCANCODE_A]) {
		object->xpos--;
	}
	
	if (keys[SDL_SCANCODE_W]) {
		object->ypos--;
	}
	
	if (keys[SDL_SCANCODE_S]) {
		object->ypos++;
	}
	
	if (keys[SDL_SCANCODE_D]) {
		object->xpos++;
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
	if (Update::playerCollision(object)) {
		object->xpos = xoud;
		object->ypos = youd;
	}

	object->update();
	
}