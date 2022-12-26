#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "def.h"
#include "object.h"

class Game {
public:
	Game();
	~Game();

private:
	bool init();
	void gameLoop();

	bool running;

	Object object;

	SDL_Window* window;
	TTF_Font* font;
};
#endif