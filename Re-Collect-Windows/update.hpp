#pragma once
#include "sdl.h"
#include "gameObject.hpp"

class Update {

public:
	void updateplayer(gameObject* Object, gameObject* Map, int border[2]);
	bool playerCollision(gameObject* Object, gameObject* Map);

private:
};
