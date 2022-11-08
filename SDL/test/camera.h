#pragma once
#include <SDL_image.h>
class Camera {
	SDL_Texture* backgroundIMG = NULL;
	int w, h;
	SDL_Point pos;

	Camera(SDL_Texture* _backgroundIMG) {
		backgroundIMG = _backgroundIMG;
		SDL_QueryTexture(backgroundIMG, NULL, NULL, &w, &h);
		pos = { 0, 0 };
	}
	
};