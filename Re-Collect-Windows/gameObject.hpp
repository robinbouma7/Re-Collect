#pragma once
#include "game.hpp"

class gameObject {

public:
	gameObject(const char* texturesheet, int x, int y, int Srcx, int Srcy, int Srcw, int Srch);
	~gameObject();

	void update();
	void render();

	int xpos;
	int ypos;

	int srcx;
	int srcy;
	int srch;
	int srcw;

	int sizew;
	int sizeh;

	

private:

	SDL_Rect srcRect, destRect;
	SDL_Texture* objTexture;
	

};