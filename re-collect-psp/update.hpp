#pragma once
#include "gameObject.hpp"

class Update {

public:
	void updateplayer(gameObject* Object, gameObject* Map);
	bool playerCollision(gameObject* Object, gameObject* Map);

private:
};
