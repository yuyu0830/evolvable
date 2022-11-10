#pragma once
#include "object.h"

class Player : public Object {
public:
	SDL_Texture* aim = NULL;
	Vector2 inScreenPos;
	float dir;
	int blockX, blockY;

	void init(Vector2 _pos, float _speed, SDL_Texture* _image, SDL_Texture* _aim);
	void update();
	void move();
	void draw();
};