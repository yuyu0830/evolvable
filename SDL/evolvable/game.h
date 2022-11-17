#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "init.h"
#include "box.h"

class Game {
public:
	Game();
	~Game();

private:
	void gameLoop();
	void draw();
	void update();
};

#endif