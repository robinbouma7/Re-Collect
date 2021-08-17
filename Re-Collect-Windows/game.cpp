#include "game.hpp"
#include "TextureManager.hpp"
#include "gameObject.hpp"
#include "update.hpp"
#include "main.hpp"
#include "discord_rpc.h"
#include <time.h>

gameObject* player;
gameObject* map;
//gameObject* player2;
Update updatefunction;

SDL_Renderer* Game::renderer = nullptr;

int menu = 0;
static int64_t StartTime;
const char* status = "status not set";
int oldScreenWidth, oldScreenHeight;

Game::Game() {

}
Game::~Game() {

}

int Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	StartTime = time(0);

	screenWidth = 800;
	screenHeight = 600;

	std::cout << "als het spel opent druk op enter om te starten.\ndeze console is voor testen en gaat in en latere versie weg.\nals je een probleem heb zeg het me maar.\n\nen trouwens, collision is er alleen op 2 100 bij 100 px vierkanten.\ndeze zijn op x:100 y:100 en x:300 y:100. (er zijn zwarte vierkanten op de map getekend waar ze zijn)\n\nde grootte van het scherm word nog veranderd." << std::endl;

	Uint32 flags = 0;

	Game::cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	else {
		flags = SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE;
	}
	SDL_SetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION, "1");
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL initialized." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window) {
			std::cout << "window created." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "renderer created." << std::endl;
				
			SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);
			std::cout << "\nrenderer size:\nwidth: " << screenWidth << "\nheight: " << screenHeight << std::endl << std::endl;
			//std::cout << "\nrenderer size check 2:\nwidth: " << Game::screenWidth << "\nheight: " << Game::screenHeight << std::endl << std::endl;
		}
		//std::cout << "\nrenderer size check:\nwidth: " << Width << "\nheight: " << Height << std::endl << std::endl;

		isRunning = true;
	}
	else {
		isRunning = false;
	}
	
	//debug rectangles to see test hitboxes
	
	r1.w = 100;
	r1.h = 100;

	
	r2.w = 100;
	r2.h = 100;
	
	//path, x, y, srcx, srcy, srcw, srch
	player = new gameObject("assets/ricardo.png", 375, 275, 0, 0, 25, 25);
	map = new gameObject("maps/test/testMap.png", 0, 0, 0, 0, Game::screenWidth, Game::screenHeight);

	player->sizeh = 50;
	player->sizew = 50;
	map->sizeh = Game::screenHeight;
	map->sizew = Game::screenWidth;
	
	
	//player2 = new gameObject("assets/ricardo.png", 75, 75);
	return 1;
}

void Game::handleEvents() {
	
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
		break;
	default:

	break;

	}
}
//int testMap[2]{ 1200, 900 };

void Game::update() {
	oldScreenWidth = screenWidth;
	oldScreenHeight = screenHeight;
	SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);
	if (oldScreenWidth != Game::screenWidth || oldScreenHeight != Game::screenHeight) {
		map->sizeh = Game::screenHeight;
		map->sizew = Game::screenWidth;
		map->srch = Game::screenHeight;
		map->srcw = Game::screenWidth;
	}
	
	updatefunction.updateplayer(player, map);

	r1.x = 100 - map->srcx;
	r1.y = 100 - map->srcy;

	r2.x = 300 - map->srcx;
	r2.y = 100 - map->srcy;
	
	//std::cout << "\nbuttons checked" << std::endl;
	//std::cout << "xpos: " << player->xpos << "\nypos: " << player->ypos << std::endl;
	//player->update();
	//player2->update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	//render stuff here
	map->render();
	player->render();
	//rectangles used for tessting hitboxes.
	//std::cout << "x: " << player->xpos << "\ny: " << player->ypos << std::endl;
	//SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	//SDL_RenderFillRect(renderer, &r1);
	//SDL_RenderFillRect(renderer, &r2);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
	
	//player2->render();

	SDL_SetCursor(Game::cursor);
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "window closed and renderer destroyed." << std::endl;
}



//discord presence
static void handleDiscordReady(const DiscordUser* connectedUser) {
	printf("\nDiscord: connected to user %s#%s - %s\n",
		connectedUser->username,
		connectedUser->discriminator,
		connectedUser->userId);
}
static void handleDiscordDisconnected(int errcode, const char* message) {
	printf("\nDiscord: disconnected (%d: %s)\n", errcode, message);
}
static void handleDiscordError(int errcode, const char* message) {
	printf("\nDiscord: error (%d: %s)\n", errcode, message);
}

void Game::InitDiscord() {
	DiscordEventHandlers handlers;
	memset(&handlers, 1, sizeof(handlers));
	handlers.ready = handleDiscordReady;
	handlers.errored = handleDiscordError;
	handlers.disconnected = handleDiscordDisconnected;

	// Discord_Initialize(const char* applicationId, DiscordEventHandlers* handlers, int autoRegister, const char* optionalSteamId)
	Discord_Initialize("876756056150265856", &handlers, 1, NULL);
}
void Game::UpdatePresence(const char* Status) {
	/*if (status != Status) {
		std::cout << "status is different. \nit was: " << status << "\nthe new one is: " << Status << std::endl;
	}*/
	status = Status;
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	
	discordPresence.details = status;
	discordPresence.startTimestamp = StartTime;
	discordPresence.largeImageKey = "re-collect-1024x1024";
	discordPresence.largeImageText = "https://robinbouma.itch.io/re-collect";
	discordPresence.partyId = "";
	discordPresence.partySize = 0;
	discordPresence.partyMax = 0;
	discordPresence.joinSecret = "";
	Discord_UpdatePresence(&discordPresence);

}