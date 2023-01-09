#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "util.h"
#include "object.h"
#include "timer.h"

#include "graphic/renderer.h"
#include "graphic/font.h"

class Game {
public:
	Game();
	~Game();

private:
	bool init();
	void gameLoop();

	bool running;

	Object object;

	float fps;
	int frameCounter;
};
#endif