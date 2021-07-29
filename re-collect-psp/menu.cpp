#include "menu.hpp"
#include "game.hpp"
#include "gameObject.hpp"
#include "main.hpp"


Game game;
Main master;
gameObject* background;

gameObject* start;
gameObject* options;
gameObject* memories;
gameObject* quitGame;
gameObject* optionsScreen;
gameObject* quitCheck;
gameObject* workInProgress;


int menustate;

bool Menu::initMenu() {

	background = new gameObject("assets/menu/background.png", 0, 0, 480, 272);

	start = new gameObject("assets/menu/start.png", 10, 250, 50, 10);
	
	options = new gameObject("assets/menu/opties.png", 70, 250, 50, 10);
	
	memories = new gameObject("assets/menu/memories.png", 360, 250, 50, 10);
	
	quitGame = new gameObject("assets/menu/quitGame.png", 420, 250, 50, 10);
	
	optionsScreen = new gameObject("assets/menu/optionsscreen.png", 75, 40, 320, 192);
	
	quitCheck = new gameObject("assets/menu/quitCheck.png", 100, 75, 150, 100);
	
	workInProgress = new gameObject("assets/menu/workInProgress.png", 100, 75, 150, 100);
	

	//cross options: x: 481, y: 480, w: 19, h: 16
	
	/*start.x = 50;
	start.y = 525;
	start.w = 150;
	start.h = 30;

	options.x = 250;
	options.y = 525;
	options.w = 150;
	options.h = 30;

	memories.x = 450;
	memories.y = 525;
	memories.w = 150;
	memories.h = 30;*/
	
	//SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);

	return true;
}
SceCtrlData ctrldata;
void Menu::updateMenu() {

	//SDL_PumpEvents();

	//const Uint8* keys = SDL_GetKeyboardState(NULL);
	sceCtrlReadBufferPositive(&ctrldata, 1);
	
	
		background->update();
		//main screen
		if (menustate == 0) {
			/*if (mousex > 25 && mousex < 175 && mousey > 525 && mousey < 555) {
				game.cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
			}
			else if (mousex > 215 && mousex < 365 && mousey > 525 && mousey < 555) {
				game.cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
			}
			else if (mousex > 440 && mousex < 590 && mousey > 525 && mousey < 555) {
				game.cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
			}
			else if (mousex > 625 && mousex < 775 && mousey > 525 && mousey < 555){
				game.cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
			}
			else {
				game.cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
			}*/
			//std::cout << "mouse x: " << mousex << "\nmouse y: " << mousey << std::endl;

			if (ctrldata.Buttons & PSP_CTRL_START) {
				master.changestate(1);
			}
			

			/*if (mouseButtons == SDL_BUTTON_LEFT) {
				//std::cout << "left mouse button pressed!" << std::endl;
				if (mousex > 25 && mousex < 175 && mousey > 525 && mousey < 555) {
					master.changestate(1);
				}
				else if (mousex > 215 && mousex < 365 && mousey > 525 && mousey < 555) {
					//options screen
					menustate = 1;
				}
				else if (mousex > 440 && mousex < 590 && mousey > 525 && mousey < 555) {
					//memories screen
					menustate = 2;
				}
				else if (mousex > 625 && mousex < 775 && mousey > 525 && mousey < 555) {
					menustate = 3;
				}
				else {

				}

			}*/
			start->update();
			options->update();
			memories->update();
			quitGame->update();
		}

		//options
		else if (menustate == 1) {
			
			/*if (keys[SDL_SCANCODE_BACKSPACE]) {
				//back to main menu
				menustate = 0;
			}
			//kruislocatie = x: 631 y: 100, w: 19, h: 16;
			if (mouseButtons == SDL_BUTTON_LEFT && mousex > 631 && mousex < 650 && mousey > 100 && mousey < 116) {
				menustate = 0;
			}*/

			optionsScreen->update();
		}

		//memories
		else if (menustate == 2) {
			
			//start->update();
			//options->update();
			//memories->update();
			//quitGame->update();
			
			/*if (keys[SDL_SCANCODE_SPACE]) {
				menustate = 0;
			}*/
			workInProgress->update();
		}

		//ask to quit game
		else if (menustate == 3) {

			/*if (mousex > 230 && mousex < 330 && mousey > 300 && mousey < 330) {
				game.cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);	
			}
			else if (mousex > 370 && mousex < 470 && mousey > 300 && mousey < 330) {
				game.cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);	
			}
			else {
				game.cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
			}

			if (mouseButtons == SDL_BUTTON_LEFT) {

				if (mousex > 230 && mousex < 330 && mousey > 300 && mousey < 330) {
					game.event.type = SDL_QUIT;
					SDL_PushEvent(&game.event);
				}
				else if (mousex > 370 && mousex < 470 && mousey > 300 && mousey < 330) {
					menustate = 0;				
				}
				else {

				}
			}*/
			//start->update();
			//options->update();
			//memories->update();
			//quitGame->update();
			quitCheck->update();
		}


		else {

		}
		
		
	
}
void Menu::renderMenu() {
	g2dClear(WHITE);
	
	background->render();

	if (menustate == 0) {
		start->render();
		options->render();
		memories->render();
		quitGame->render();
	}

	else if (menustate == 1) {
		optionsScreen->render();
	}

	else if (menustate == 2) {
		workInProgress->render();
	}

	else if (menustate == 3) {
		//start->render();
		//options->render();
		//memories->render();
		//quitGame->render();
		quitCheck->render();
	}

	else {
		//std::cout << "error, menu state bestaat niet. de waarde er van was: " << menustate << std::endl;
		//std::cout << "menustate word veranderd naar 0" << std::endl;
		menustate = 0;
	}
	
	
	//SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	//SDL_RenderFillRect(Game::renderer, &start);
	//SDL_RenderFillRect(Game::renderer, &options);
	//SDL_RenderFillRect(Game::renderer, &memories);
	
	//SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	g2dFlip(G2D_VSYNC);
}