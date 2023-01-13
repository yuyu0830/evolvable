#ifndef POSITION_H
#define POSITION_H

#include <SDL.h>

#include "util.h"

class Position {
public:
	static SDL_FPoint add(SDL_FPoint a, SDL_FPoint b);

	SDL_FPoint get();
	float getX();
	float getY();
	
	void set(float _x, float _y);
	void set(int _x, int _y);
	void set(SDL_Point pos);
	void move(float angle, float speed);

private:
	float x;
	float y;
};

#endif