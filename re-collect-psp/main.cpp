#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include "glib2d.h"
#include "game.hpp"
#include "main.hpp"
#include "menu.hpp"

PSP_MODULE_INFO("Re-Collect", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);



int state = 0;

//stops the game.
//this is just code that works, so dont change this. (upcoming 3 functions)
int exit_callback(int arg1, int arg2, void *common) {
    sceKernelExitGame();
    return 0;
}


int callbackthread(SceSize args, void *argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);

    sceKernelSleepThreadCB();
    return 0;
}


void setupcallbacks () {
    int thid = sceKernelCreateThread("update_thread", callbackthread, 0x11, 0xfa0, 0, NULL);
    if (thid >= 0) {
        sceKernelStartThread(thid, 0, NULL);
    }
}


int main() {

	setupcallbacks();
	//Main master;
	//const int fps = 60;
	//const int frameDelay = 1000 / fps;

	

	//Uint32 framestart;
	//int frametime;

	Game game;
	Menu menu;
	
	
	
	
	game.init();
	
	if (!menu.initMenu()) {
		game.isRunning = false;
	}
	/*gamestates:
	0: main menu
	1: main game
	*/

	while (game.running()) {
		
		//framestart = SDL_GetTicks();

		if (state == 0) {
			//game.handleEvents();
			menu.updateMenu();
			menu.renderMenu();
		}

		if (state == 1) {
			//game->handleEvents();
			game.update();
			game.render();
		}
		if (state < 0 || state > 1) {
			//std::cout << "non existent game state set.\ngame state value is: " << state << std::endl;
			game.isRunning = false;
		}

		//frametime = SDL_GetTicks() - framestart;

		//if (frameDelay > frametime) {
		//	SDL_Delay(frameDelay - frametime);
		//}

	}
}

void Main::changestate(int newState) {
	state = newState;
	//std::cout << "changed gamestate to: " << state << std::endl;
}