#include "glib2d.h"
#include "gameObject.hpp"
#include "textureManager.hpp"
#include "game.hpp"

gameObject::gameObject(const char* texturesheet, int x, int y, int w, int h) {
	objTexture = TextureManager::loadTexture(texturesheet);
	xpos = x;
	ypos = y;
	width = w;
	height = h;
}
void gameObject::update() {
	//hoeft niks mee te gebeuren.
}

void gameObject::render() {
	//SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
	g2dBeginRects(objTexture);
    if (objTexture == NULL) {
        g2dSetColor(RED);
    }
    g2dSetCoordMode(G2D_UP_LEFT);
    g2dSetAlpha(255);
    g2dSetScaleWH(width,height);
    g2dSetCoordXY(xpos,ypos);
    g2dSetRotation(0);
    g2dAdd();
    g2dEnd();
}