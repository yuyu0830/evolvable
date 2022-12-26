#ifndef OBJECT_H
#define OBJECT_H

#include <SDL_Image.h>
#include <iostream>

#include "graphic.h"
#include "unit.h"
#include "UI.h"

class Object {
public:
	bool init(SDL_Window* window);
	void tmp(); //юс╫ц
	void update();
	void draw();

private:
	SDL_Renderer* renderer;
	UI ui[3];
	Unit unit[3];
};


#endif