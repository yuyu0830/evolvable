#ifndef TILE_H
#define TILE_H

#include <iostream>

#include "../frame/graphic.h"
#include "../frame/object.h"

class Tile : public Object {
public:
	~Tile();

	void update();

protected:
	int tileNum;
	static int staticTileNum;
};

#endif