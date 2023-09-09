#ifndef UNIT_H
#define UNIT_H

#include "Object.h"

class Unit : public Object {
public:
	//virtual void load(SDL_Renderer* renderer, const char* fileDir, ObjectData data, UnitData udata);
	//virtual void update(Input* input);
	//virtual void draw(SDL_Renderer* renderer);

protected:
	bool invincible; //power overwhelming
	bool attackable; //Can this Unit attack something?

	float maxHP;
	float currentHP;

	float atk;
	float range;
	float speed;
};

#endif