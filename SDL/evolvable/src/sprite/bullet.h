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
	void init(char _owner[], float _speed);
	void draw(SDL_Renderer* renderer, SDL_FPoint cameraPos);
	void create(float _dir, SDL_FPoint _pos);
	void update(bool map[100][100]);

private:
	SDL_Texture* bulletImg;
	SDL_Texture* bulletDisappearImg;

protected:
	char owner[20];
	
	short bulletCounter;
	int w, h;
	float speed;

	bool active[BULLETSIZE];
	bool disappear[BULLETSIZE];
	int disappearTimer[BULLETSIZE];
	SDL_FPoint dir[BULLETSIZE];
	SDL_FPoint pos[BULLETSIZE];
	std::vector<int> activeBullet;

	friend class Object;
};

#endif