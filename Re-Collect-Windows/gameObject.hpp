#pragma once
#include "game.hpp"

class gameObject {

public:
	gameObject(const char* texturesheet, int x, int y);
	~gameObject();

	void update();
	void render();

	int xpos;
	int ypos;

	bool up;
	bool down;
	bool left;
	bool right;

private:


	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

};