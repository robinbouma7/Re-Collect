#pragma once


#include "sdl.h"
#include "gameObject.hpp"

class Update {

public:
	void updateplayer(gameObject* Object, gameObject* Map);
	bool playerCollision(gameObject* Object, gameObject* Map);
	int ableToInteract(gameObject* Object, gameObject* Map);
	void renderText(TTF_Font* font, int screenwidth, int screenheight);

	bool interacting = false;
	int interactState;
	int message = 0;
private:
};
