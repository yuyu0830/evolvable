#ifndef UI_H
#define UI_H

#include "graphic.h"

class UI :public Graphic {
public:
	virtual void update(Input* input);
	virtual void draw(SDL_Renderer* renderer);

private:

};

#endif