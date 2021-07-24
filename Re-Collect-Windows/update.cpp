#include "update.hpp"
#include "game.hpp"
#include <iostream>
#include "SDL.h"

//bool keys[322];


void Update::updateplayer(gameObject* Object) {

	//SDL_Event event;
	gameObject* object = Object;

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	std::cout << keys << std::endl;

	

	
	//SDL_PollEvent(&event);

	/*if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			std::cout << "key down" << std::endl;
			keys[event.key.keysym.sym] = true;
			break;

		case SDL_KEYUP:
			std::cout << "key up" << std::endl;
			keys[event.key.keysym.sym] = false;
			break;
		}
	}*/

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
	
	object->update();

	/*old code, didn't work
	
	SDL_PollEvent(&event);
	

	switch (event.key.keysym.sym) {
		case SDLK_w:
			object->ypos--;
			std::cout << "w pressed" << std::endl;
		break;
		case SDLK_a:
			object->xpos--;
			std::cout << "a pressed" << std::endl;
		break;
		case SDLK_d:
			object->xpos++;
			std::cout << "d pressed" << std::endl;
		break;
		case SDLK_s:
			object->ypos++;
			std::cout << "s pressed" << std::endl;
		break;
		default:
			std::cout << "none of the 4 buttons pressed" << std::endl;
		break;
	}*/


	
	
}