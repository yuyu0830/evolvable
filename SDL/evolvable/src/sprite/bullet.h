#ifndef BULLET_H_
#define BULLET_H_

#include <ostream>
#include <SDL.h>
#include "../box.h"
#include "../draw.h"

class Bullet {
public:
	~Bullet();
	void init(char* _owner, SDL_Texture* _bulletImg, float _speed);
	void draw(SDL_Renderer* renderer);
	void create(float _dir, SDL_FPoint _pos);

private:
	SDL_Texture* bulletImg;

protected:
	char owner[20];
	
	short bulletCounter;
	int w, h;
	float speed;

	bool active[BULLETSIZE];
	float dir[BULLETSIZE];
	SDL_FPoint pos[BULLETSIZE];

	friend class Object;
};

#endif