#ifndef UNIT_H
#define UNIT_H

#include "graphic.h"
#include "def.h"

class Unit : public Graphic {
public:
	virtual void update();
	virtual void draw(SDL_Renderer* renderer);

private:

};

#endif