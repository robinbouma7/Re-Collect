#include "TextureManager.hpp"
#include "SDL_ttf.h"

SDL_Surface* surfaceMessage;

SDL_Texture* TextureManager::loadTexture(const char* texture) {
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}
void TextureManager::loadFont(const char* text, TTF_Font* font, SDL_Color color, int x, int y) {
	
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color);
	
	if (surfaceMessage == NULL) {
		std::cout << "failed to load message surface: " << SDL_GetError() << std::endl;
	}
	else {
		SDL_Texture* message = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
		if (message == NULL) {
			std::cout << "failed to load message sprite: " << SDL_GetError() << std::endl;
		}
		else {
			src.x = 0;
			src.y = 0;
			src.w = surfaceMessage->w;
			src.h = surfaceMessage->h;

			dst.x = x;
			dst.y = y;
			dst.w = src.w;
			dst.h = src.h;

			SDL_RenderCopy(Game::renderer, message, &src, &dst);
			SDL_FreeSurface(surfaceMessage);
			SDL_DestroyTexture(message);
		}
	}
	//return message;
}