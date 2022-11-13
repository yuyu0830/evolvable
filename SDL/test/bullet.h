#pragma once
#include <SDL_image.h>
#include "object.h"
#include "box.h"

class Bullet : public Object{
public:
	bool active;
	float speed;
	Vector2 dir;

	Bullet() {};

	~Bullet() {
		SDL_DestroyTexture(image);
	}
	//void Reset(int _bulletNum);
	//void Create(Vector2 _pos, int _speed);
	//void Calc();
	//void bulletDraw();
};