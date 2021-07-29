#pragma once

#include <iostream>
#include "gameObject.hpp"

class Game {

public:
	Game();
	~Game();

	void init();

	void handleEvents();
	void update();
	void render();

	bool running() { return isRunning;  }

	
	bool isRunning;
	

private:
	
	
	
};
