#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "box.h"
#include "input.h"
#include "draw.h"
#include "object.h"

class Game {
public:
	Game();
	~Game();

private:
	bool init();
	void gameLoop();
	void draw();
	void update();

	App app;
	Input input;
	Timer timer;
	
	Object object;

	bool running;
	bool infoMode;

	//frame
	float fps;
	int frameCounter;
};
#endif