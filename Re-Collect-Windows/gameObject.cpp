

#include "gameObject.hpp"
#include "textureManager.hpp"
#include "game.hpp"

gameObject::gameObject(const char* texturesheet, int x, int y, int Srcx, int Srcy, int Srcw, int Srch) {
	objTexture = TextureManager::loadTexture(texturesheet);
	xpos = x;
	ypos = y;
	srcx = Srcx;
	srcy = Srcy;
	srcw = Srcw;
	srch = Srch;
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

	


	srcRect.h = srch;
	srcRect.w = srcw;
	srcRect.x = srcx;
	srcRect.y = srcy;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = sizew;
	destRect.h = sizeh;
}

void gameObject::render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
