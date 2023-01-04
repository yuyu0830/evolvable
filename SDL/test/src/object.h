#ifndef OBJECT_H
#define OBJECT_H

#include <SDL_Image.h>
#include <iostream>

#include "util.h"

#include "./sprite/UI.h"
#include "./sprite/graphic.h"
#include "./sprite/unit.h"
#include "./sprite/player.h"
#include "./sprite/background.h"

#include "collider.h"

class Object {
public:
	int update();
	int draw();

	//�ѹ� ���
	bool init(SDL_Window* window);

	//�ݺ� ���
	void initInput();
	void boom();
	bool eventHandling();
	
	
	~Object();

private:
	SDL_Renderer* renderer;
	Input* input;

	Background background;
	Collider* colliderPointer[TAG_NUMBER];

	bool colliderTriggerTable[TAG_NUMBER][TAG_NUMBER];
};

#endif