#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL_Image.h>

#include "../draw.h"
#include "../util.h"
#include "../position.h"


class Graphic {
public:
	Graphic* create(int x, int y, type type);

	Position position; //Object Position ���� ��ġ
	Size size;

protected:
	SDL_Texture* frame[5];
};

#endif