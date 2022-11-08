#pragma once
#include <SDL_image.h>
#include "object.h"
#include "box.h"

class Bullet {
public:
	int bulletNum;
	float speed;
	bool active[BULLETSIZE];
	Vector2 pos[BULLETSIZE];
	Vector2 dir[BULLETSIZE];
	SDL_Texture* image = NULL;

	Bullet() {
		bulletNum = 0;
		speed = 0.0f;
		Vector2 empty = Vector2(0, 0);
		for (int i = 0; i < BULLETSIZE; i++) {
			active[i] = 0;
			pos[i] = empty;
			dir[i] = empty;
		}
	}

	void Reset(int _bulletNum);
	void Create(Vector2 _pos, int _speed);
	void Calc();
	void bulletDraw();
};