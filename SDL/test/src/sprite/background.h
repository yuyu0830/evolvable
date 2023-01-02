#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "graphic.h"

class Background : public Graphic {
public:
	virtual void load(SDL_Renderer* renderer, const char* fileDir);
	virtual void draw(SDL_Renderer* renderer);

protected:

};

#endif