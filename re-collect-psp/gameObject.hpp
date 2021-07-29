#pragma once
#include "game.hpp"
#include "glib2d.h"

class gameObject {

public:
	gameObject(const char* texturesheet, int x, int y, int w, int h);
	~gameObject();

	void update();
	void render();

	int xpos;
	int ypos;
	int width;
	int height;

	int srcx;
	int srcy;
	int srch;
	int srcw;

	int sizew;
	int sizeh;

	

private:

	
	g2dTexture* objTexture;
	

};