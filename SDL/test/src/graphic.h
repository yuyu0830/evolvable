#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL_Image.h>

#include "draw.h"
#include "def.h"

class Graphic {
public:
	void load(objectData _data, SDL_Renderer* renderer, const char* file, SDL_Rect dst);
	virtual void update(Input* input) = 0;
	virtual void draw(SDL_Renderer* renderer) = 0;

protected:
	objectData data;
	SDL_Texture* texture;
	SDL_Rect pos;
};

#endif