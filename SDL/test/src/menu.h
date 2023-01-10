#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>

#include "draw.h"
#include "util.h"

#include "./sprite/UI.h"

class Menu {
public:
	Menu();

	void update();
	void draw();

	void drawBackgroundColor(SDL_Color color);
	void scenceChange(menuScene scene);

protected:
	int scence;
	
	SDL_Texture* tile[5];
};

#endif