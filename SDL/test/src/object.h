#ifndef OBJECT_H
#define OBJECT_H

#include <SDL_Image.h>
#include <iostream>

#include "util.h"

#include "./sprite/UI.h"
#include "./sprite/graphic.h"
#include "./sprite/unit.h"
#include "./sprite/player.h"
#include "./sprite/background.h"

class Object {
public:
	bool init(SDL_Window* window);
	int update();
	int draw();
	bool eventHandling();
	~Object();

private:
	Player player;
	UI button[4];
	Background background;

	TTF_Font* tmpFont;
	SDL_Renderer* renderer;
	Input* input;

	bool colliderTriggerTable[SHAPE_NUMBER][SHAPE_NUMBER];
};

#endif