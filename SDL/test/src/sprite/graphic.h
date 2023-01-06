#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL_Image.h>

#include "../draw.h"
#include "../util.h"
#include "../position.h"


class Graphic {
public:
	void dataInput(ObjectData data);
	Position position;

protected:
	Size size;

	char name[20];
	int tag;
	int unitNum;
};

#endif