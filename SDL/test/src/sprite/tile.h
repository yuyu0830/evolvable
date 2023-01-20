#ifndef TILE_H
#define TILE_H

#include "graphic.h"

#include "../object.h"

class Tile : public Object {
public:
	Tile(int x, int y, type _type) : Object(x, y, _type) {
		tileNum = staticTileNum++;
	};
	~Tile();

	void update();

protected:
	int tileNum;
	static int staticTileNum;
};

#endif