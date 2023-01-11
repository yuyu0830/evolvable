#ifndef TILE_H
#define TILE_H

#include "graphic.h"

class Tile : public Graphic {
public:
	Graphic* next();

protected:
	bool invincible;
	float atk;
	float maxHP;
	float curHP;
	float speed;
};

#endif