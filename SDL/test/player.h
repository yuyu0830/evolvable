#pragma once
#include "object.h"
#include <SDL.h>

class Player : public Object {
public:
	SDL_Texture* aim = NULL;
	SDL_Texture* caterpillar = NULL;
	Vector2 inScreenPos;
	float dir;
	float caterpillarDir;
	int blockX, blockY;
	int caterpillarNum;
	Vector2 vertex[4];
	bool led[4];

	~Player() {
		SDL_DestroyTexture(aim);
		SDL_DestroyTexture(caterpillar);
		SDL_DestroyTexture(image);
	}

	void init(Vector2 _pos, float _speed, SDL_Texture* _image, SDL_Texture* _aim, SDL_Texture* _catepiller);
	void update();
	void move(float moveX, float moveY);
	void draw();
};