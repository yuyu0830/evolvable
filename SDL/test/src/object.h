#ifndef OBJECT_H
#define OBJECT_H

#include <SDL_Image.h>
#include <iostream>

#include "graphic.h"
#include "def.h"
#include "unit.h"
#include "UI.h"

class Object {
public:
	bool init(SDL_Window* window);
	void tmp();
	int update();
	int draw();
	bool eventHandling();
	~Object();

private:
	SDL_Renderer* renderer;
	Unit* unit;
	UI* ui;
	Input* input;
};


#endif