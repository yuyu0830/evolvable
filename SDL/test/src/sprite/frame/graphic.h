#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL_Image.h>

#include "partsManager.h"
#include "parts.h"

#include "../../util.h"
#include "../../position.h"

#include "../../graphic/draw.h"

class Graphic {
public:
	Graphic();
	~Graphic();
	void load(type _type);
	void draw(SDL_FPoint point); //draw All parts

protected:
	int partAmount;

	Parts* part[MAX_PARTS_NUMBER];
};

#endif