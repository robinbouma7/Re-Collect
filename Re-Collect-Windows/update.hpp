#pragma once
#include "sdl.h"
#include "gameObject.hpp"

class Update {

public:
	void updateplayer(gameObject* Object);
	bool playerCollision(gameObject* Object);

private:
};
