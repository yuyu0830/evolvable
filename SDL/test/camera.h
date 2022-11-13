#pragma once
#include <SDL_image.h>
#include "box.h"

class Camera {
public:
	SDL_Color color = { 0, 0, 0 };
	SDL_Texture* backgroundIMG = NULL;
	SDL_Texture* wall = NULL;
	SDL_Texture* texture = NULL;
	SDL_Surface* text = NULL;
	int imgWidth, imgHeight;
	short map[75][75];
	SDL_Point pos;

	~Camera() {
		SDL_DestroyTexture(backgroundIMG);
		SDL_DestroyTexture(wall);
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(text);
	};
	void init(SDL_Texture* _backgroundIMG, SDL_Texture* _wall);
	void drawBackground();
	void drawWalls();
	void drawDeveloperMode();
	void update();
	Vector2 playerCollisionCheck(Vector2 vec);
	void makeMap();
};