#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL_Image.h>

#include "../draw.h"
#include "../util.h"
#include "../position.h"


class Graphic {
public:
	~Graphic();
	virtual void update(Input* input);
	virtual void draw(SDL_Renderer* renderer);
	Position position;

protected:
	SDL_Texture* texture;
	Size size;

	char name[20];
	int tag;
	int unitNum;
};

#endif