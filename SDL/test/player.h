#pragma once
#include "object.h"

class Player : public Object {
public:
	float dir;

	void init(int _x, int _y, SDL_Texture* _texture);
	void dirUpdate();
};