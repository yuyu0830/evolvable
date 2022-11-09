#pragma once
#include <SDL_image.h>
#include "box.h"

class Camera {
public:
	SDL_Texture* backgroundIMG = NULL;
	SDL_Texture* wall = NULL;
	int imgWidth, imgHeight;
	short map[75][75];
	SDL_Point pos;

	Camera() {};
	void init(SDL_Texture* _backgroundIMG, SDL_Texture* _wall);
	void drawBackground();
	void drawWall();
	void drawWalls();
	void update();
	void makeMap();
};