#ifndef PLAYER_H_
#define PLAYER_H_

#include <ostream>

#include <SDL.h>

#include "../box.h"
#include "../draw.h"
#include "bullet.h"

class Player {
public:
	~Player();
	void init(SDL_FPoint _pos, float _speed, float _rotateSpeed);
	void update(Input* input);
	void draw(SDL_Renderer* renderer);

private:
	SDL_Texture* fireDirImg;
	SDL_Texture* caterpillar;
	SDL_Texture* turret;

	Bullet bullet;

	SDL_FPoint pos;
	SDL_FPoint inScreenPos;
	SDL_FPoint vertex[4];

	SDL_Rect caterpillarRect;

	int fw, fh;
	int w, h;
	
	char name[20];
	float speed;
	float rotateSpeed;
	float fireDir;
	float caterpillarDir;
	short caterpillarNum;

	bool led[4];
	
	friend class Object;
};
#endif