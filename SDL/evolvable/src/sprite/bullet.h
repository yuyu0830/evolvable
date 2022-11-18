#ifndef BULLET_H_
#define BULLET_H_

#include <iostream>
#include <vector>
#include <SDL.h>
#include "../box.h"
#include "../draw.h"

class Bullet {
public:
	~Bullet();
	void init(char _owner[], SDL_Texture* _bulletImg, float _speed);
	void draw(SDL_Renderer* renderer);
	void create(float _dir, SDL_FPoint _pos);
	void update();

private:
	SDL_Texture* bulletImg;

protected:
	char owner[20];
	
	short bulletCounter;
	int w, h;
	float speed;

	bool active[BULLETSIZE];
	SDL_FPoint dir[BULLETSIZE];
	SDL_FPoint pos[BULLETSIZE];
	std::vector<int> activeBullet;

	friend class Object;
};

#endif