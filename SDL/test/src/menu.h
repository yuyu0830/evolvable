#ifndef Menu_H
#define Menu_H

#include <SDL.h>
#include <SDL_image.h>

#include "draw.h"
#include "util.h"

#include "./sprite/UI.h"

class Menu {
public:
	Menu();

	void update(Input* input);
	void draw(SDL_Texture* renderer);
	void scenceChange(int nextScence);

protected:
	int scence;

	SDL_Texture* tile[5];
	SDL_Texture* button[2];

	UI* button[3];
};

#endif