#include "bullet.h"

Bullet::~Bullet() {
	SDL_DestroyTexture(bulletImg);
}

void Bullet::init(char _owner[], SDL_Texture* _bulletImg, float _speed) {
	strcpy_s(owner, _owner);
	bulletImg = _bulletImg;
	speed = _speed;

	bulletCounter = 0;

	SDL_QueryTexture(bulletImg, NULL, NULL, &w, &h);

	for (int i = 0; i < BULLETSIZE; i++) {
		active[i] = false;
		pos[i] = { 0, 0 };
		dir[i] = 0.0f;
	}

	printf("%s's Bullet Initialize Complete!\n", owner);
}

void Bullet::draw(SDL_Renderer* renderer) {
	for (int i = 0; i < BULLETSIZE; i++) {
		if (active[i]) {
			drawTexture(renderer, (int)pos[i].x, (int)pos[i].y, bulletImg);
		}
	}
}

void Bullet::create(float _dir, SDL_FPoint _pos) {
	if (bulletCounter < BULLETSIZE) {
		int bulletNum = 0;
		while (active[bulletNum]) {
			bulletNum++;
		};
		active[bulletNum] = true;
		printf("%d\n",bulletNum);
	}
}