#pragma once
#include <SDL_image.h>

class Object {
public:
	float x;
	float y;
	float w;
	float h;

	SDL_Texture* image = NULL;

	void move(float _x, float _y);
	void objDraw(float dir = 0);
};