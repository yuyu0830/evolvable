#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "font.h"
#include "util.h"
#include "input.h"
#include "timer.h"

#include "./graphic/renderer.h"
#include "./graphic/draw.h"

//#include "sprite/frame/object.h"
//#include "sprite/frame/graphic.h"
//#include "sprite/frame/UI.h"

//#include "sprite/UI/background.h"
//#include "sprite/UI/tile.h"

class Game {
public:
	Game();

private:
	bool init();
	void gameLoop();

	int draw();
	int update();

	void tmpset();

	bool running;
};
#endif