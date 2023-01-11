#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <new>

#include <SDL_Image.h>
#include <SDL_ttf.h>

#include "util.h"

#include "./sprite/UI.h"
#include "./sprite/graphic.h"
#include "./sprite/unit.h"
#include "./sprite/player.h"

#include "collider.h"
#include "input.h"

class Object {
public:
	int update();
	int draw();

	//반복 사용
	void collisionCheck();

	//한번 사용
	void init();
	void initVariable();

private:

	bool isInGame;
	bool colliderTriggerTable[TAG_NUMBER][TAG_NUMBER];
};

#endif