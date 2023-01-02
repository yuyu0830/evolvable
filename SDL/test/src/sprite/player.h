#ifndef PLAYER_H
#define PLAYER_H

#include "unit.h"

class Player : public Unit {
public:
	virtual void load(SDL_Renderer* renderer, const char* fileDir, ObjectData data, UnitData udata);
	virtual void update(Input* input);
	//virtual void draw(SDL_Renderer* renderer);

private:
	float speed;
};

#endif