#include "bullet.h"

Bullet::~Bullet() {
	SDL_DestroyTexture(bulletImg);
}

void Bullet::init(char _owner[], float _speed) {
	strcpy_s(owner, _owner);
	speed = _speed;

	bulletCounter = 0;

	SDL_QueryTexture(bulletImg, NULL, NULL, &w, &h);

	for (int i = 0; i < BULLETSIZE; i++) {
		active[i] = false;
		pos[i] = { 0, 0 };
		dir[i] = { 0.f, 0.f };
		disappear[i] = false;
		disappearTimer[i] = 0;
	}

	printf("%s's Bullet Initialize Complete!\n", owner);
}

void Bullet::draw(SDL_Renderer* renderer, SDL_FPoint cameraPos) {
	for (int i = 0; i < BULLETSIZE; i++) {
		if (active[i]) {
			if (isin(pos[i].x, cameraPos.x, cameraPos.x + WINDOW_WIDTH) && isin(pos[i].y, cameraPos.y, cameraPos.y + WINDOW_HEIGHT)) {
				int x = (int)(pos[i].x - cameraPos.x - w / 2);
				int y = (int)(pos[i].y - cameraPos.y - h / 2);
				if (disappear[i]) {
					int a = (disappearTimer[i] / 20) * 20;
					int b = ((disappearTimer[i] / 10) % 2) * 20;
					drawTextureA(renderer, { b, a, 20, 20 }, x, y, bulletDisappearImg);
				}
				else {
					drawTexture(renderer, x, y, bulletImg);
				}
			}
		}
	}
}

void Bullet::create(float _dir, SDL_FPoint _pos) {
	if (bulletCounter < BULLETSIZE) {
		bulletCounter++;
		int bulletNum = 0;
		while (active[bulletNum]) {
			bulletNum++;
		};
		active[bulletNum] = true;
		pos[bulletNum] = _pos;
		dir[bulletNum] = { sin(_dir / RADIAN) * speed , cos(_dir / RADIAN) * speed  * -1};
	}
}

void Bullet::update(bool map[100][100]) {
	int count = 0;
	for (int i = 0; i < BULLETSIZE; i++) {
		if (active[i]) {
			if (disappear[i]) {
				if (disappearTimer[i]++ >= 40) {
					active[i] = false;
					disappear[i] = false;
					disappearTimer[i] = 0;
				}
			}
			else {
				count++;
				pos[i].x += dir[i].x;
				pos[i].y += dir[i].y;
				SDL_Point a = posToTile({ pos[i].x, pos[i].y });
				if (map[a.x][a.y]) {
					disappear[i] = true;
				}
			}
		}
		if (count == bulletCounter) {
			break;
		}
	}
}