#ifndef OBJECT_H
#define OBJECT_H

#include <SDL_Image.h>
#include <iostream>

#include "graphic.h"
#include "def.h"
#include "unit.h"
#include "UI.h"
#include "Player.h"

class Object {
public:
	bool init(SDL_Window* window);
	void tmp(); //юс╫ц
	int update();
	int draw();
	bool eventHandling();
	~Object();

private:
	SDL_Renderer* renderer;
	Input* input;

	SDL_Texture* background;

	Unit* unit[1024];
	UI* ui;
};

#endif