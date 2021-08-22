#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "gameObject.hpp"
#include "SDL_ttf.h"

class Game {

public:
	Game();
	~Game();

	int init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning;  }

	void InitDiscord();
	void UpdatePresence(const char* status);



	static SDL_Renderer* renderer;
	bool isRunning;
	SDL_Cursor* cursor;
	SDL_Event event;
	int screenWidth;
	int screenHeight;
	TTF_Font* comicSans;

private:
	int cnt = 0;
	SDL_Window* window;
	SDL_Rect r1;
	SDL_Rect r2;
	
};
