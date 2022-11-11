#pragma once
#include "object.h"

class Player : public Object {
public:
	SDL_Texture* aim = NULL;
	SDL_Texture* caterpillar = NULL;
	Vector2 inScreenPos;
	float dir;
	float caterpillarDir;
	int blockX, blockY;
	int caterpillarNum;

	void init(Vector2 _pos, float _speed, SDL_Texture* _image, SDL_Texture* _aim, SDL_Texture* _catepiller);
	void update();
	void move();
	void draw();
};