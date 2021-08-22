#pragma once

#include "game.hpp"

class TextureManager {

public:
	static SDL_Texture* loadTexture(const char* filename);
	void loadFont(const char* text, TTF_Font* font, SDL_Color color, int x, int y);

	SDL_Rect src, dst;
};