#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "renderer.h"
#include "font.h"
#include "util.h"
#include "object.h"
#include "timer.h"

#include "sprite/graphic.h"
#include "sprite/UI.h"
#include "sprite/background.h"
#include "sprite/tile.h"

class Game {
public:
	Game();

private:
	bool init();
	void gameLoop();

	int draw();
	int update();

	void tmpset();

	Tile* tile;
	UI* button;
	Background background;


	bool running;
};
#endif