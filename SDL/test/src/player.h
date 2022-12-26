#ifndef PLAYER_H
#define PLAYER_H

#include "def.h"
#include "unit.h"

class Player : public Unit {
public:
	Player(float _speed);
	virtual void update(Input* input);
	virtual void draw(SDL_Renderer* renderer);

private:
	float speed;
};

#endif