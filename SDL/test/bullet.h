#pragma once
#include <SDL_image.h>
#include "object.h"
#include "box.h"

class Bullet {
public:
	int bulletNum;
	bool active[BULLETSIZE];
	float speed[BULLETSIZE];
	Vector2 pos[BULLETSIZE];
	Vector2 dir[BULLETSIZE];
	SDL_Texture* image = NULL;

	Bullet() {
		bulletNum = 0;
		Vector2 empty = Vector2(0, 0);
		for (int i = 0; i < BULLETSIZE; i++) {
			active[i] = 0;
			speed[i] = 0.0f;
			pos[i] = empty;
			dir[i] = empty;
		}
	}

	void Reset(int _bulletNum);
	void Create(int _x, int _y, int _speed);
	void Calc();
	void bulletDraw();
};