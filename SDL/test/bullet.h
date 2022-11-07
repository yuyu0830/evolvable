#pragma once
#include <SDL_image.h>
#include "object.h"
#include "box.h"

class Bullet : public Object {
public:
	int bulletNum;
	bool active[BULLETSIZE];
	float speed[BULLETSIZE];
	Vector2 dir[BULLETSIZE];
	SDL_Texture* image = NULL;

	Bullet() {
		bulletNum = 0;
		for (int i = 0; i < BULLETSIZE; i++) {
			active[i] = 0;
			speed[i] = 0.0f;
			dir[i] = Vector2(0, 0);
		}
	}

	void Reset(int _bulletNum);
	void Create(int _x, int _y, int _speed, SDL_Texture* _texture);
	void Calc();
};