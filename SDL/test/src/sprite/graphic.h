#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL_Image.h>

#include "../draw.h"
#include "../util.h"
#include "../position.h"


class Graphic {
public:
	Graphic* create(Position p, type type, );
	Graphic* getNextPtr();
	Graphic* getPriviousPtr();
	void setNextPtr(Graphic* ptr);
	void setPriviousPtr(Graphic* ptr);

	Position position;


protected:
	Size size;
	Graphic* nextPtr = NULL;
	Graphic* priviousPtr = NULL;

	type type;
	static int nuitNum;
};

#endif