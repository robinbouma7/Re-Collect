#pragma once
#include "glib2d.h"
#include "game.hpp"

class TextureManager {

public:
	static g2dTexture* loadTexture(const char* filename);

};