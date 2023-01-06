#ifndef POSITION_H
#define POSITION_H

#include <SDL.h>

#include "util.h"

class Position {
public:
	SDL_FPoint get();
	void set(float _x, float _y);
	void set(int _x, int _y);
	void set(SDL_Point pos);
	void move(float angle, float speed);

private:
	float x;
	float y;
};

#endif