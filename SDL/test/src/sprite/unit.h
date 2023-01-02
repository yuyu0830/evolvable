#ifndef UNIT_H
#define UNIT_H

#include "graphic.h"

class Unit : public Graphic {
public:
	virtual void load(SDL_Renderer* renderer, const char* fileDir, ObjectData data, UnitData udata);
	virtual void update(Input* input);
	//virtual void draw(SDL_Renderer* renderer);

protected:
	bool invincible;
	float atk;
	float maxHP;
	float curHP;
	float speed;
};

#endif