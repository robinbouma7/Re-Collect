

#include "gameObject.hpp"
#include "textureManager.hpp"
#include "game.hpp"

gameObject::gameObject(const char* texturesheet, int x, int y) {
	objTexture = TextureManager::loadTexture(texturesheet);
	xpos = x;
	ypos = y;
}
void gameObject::update() {

	//SDL_Event event;
	/*if (left) {
		xpos--;
	}
	else {
		
	}
	if (right) {
		xpos++;
	}
	else {

	}
	if (up) {
		ypos--;
	}
	else {

	}
	if (down) {
		ypos++;
	}
	else {

	}*/


	srcRect.h = 25;
	srcRect.w = 25;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void gameObject::render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}