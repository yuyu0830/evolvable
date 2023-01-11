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

	//�ݺ� ���
	void collisionCheck();

	//�ѹ� ���
	void init();
	void initVariable();

private:

	bool isInGame;
	bool colliderTriggerTable[TAG_NUMBER][TAG_NUMBER];
};

#endif