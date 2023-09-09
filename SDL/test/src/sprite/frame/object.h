#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include <new>

#include <SDL_Image.h>
#include <SDL_ttf.h>

#include "graphic.h"
#include "partsManager.h"

#include "../../util.h"
#include "../../position.h"
#include "../../collider.h"
#include "../../input.h"

class Object {
public:
	void draw();
	virtual void update() = 0;
	//each object has different update scripts

	SDL_FPoint getCenterFPoint();
	SDL_Point getCenterPoint();

	~Object();
	//set all pointer variable to NULL

	Position position;
	Size size;

protected:
	Graphic* graphic;
	type objectType;
	tag objectTag;

	int objectNumber; 
	static int staticObjectNumber;

	bool activate;
};

#endif