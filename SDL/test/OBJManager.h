#pragma once
#include "player.h"
#include "bullet.h"
#include "box.h"
#include <SDL_image.h>

class OBJManager {
public:
	Player player;
	Bullet bullet;

	OBJManager() {};
};