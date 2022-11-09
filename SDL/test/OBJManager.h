#pragma once
#include "player.h"
#include "bullet.h"
#include "box.h"
#include <SDL_image.h>

class OBJManager {
public:
	Player player;
	Bullet bullet[100];
	int bulletNum = 0;

	OBJManager() {};
	void BulletCreate();
	void BulletUpdate();
	void BulletDraw();
};