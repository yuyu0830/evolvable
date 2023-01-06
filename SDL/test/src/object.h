#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>

#include <SDL_Image.h>
#include <SDL_ttf.h>

#include "util.h"
#include "menu.h"

#include "./sprite/UI.h"
#include "./sprite/graphic.h"
#include "./sprite/unit.h"
#include "./sprite/player.h"

#include "collider.h"

class Object {
public:
	int update();
	int draw();

	//반복 사용
	void collisionCheck();
	bool eventHandling();

	//한번 사용
	bool init(SDL_Window* window);
	void initInput();
	void initVariable();

	~Object();

private:
	SDL_Renderer* renderer;
	Input* input;

	Menu* menu;
	//Graphic* graphic[TAG_NUMBER];

	bool isInGame;
	bool colliderTriggerTable[TAG_NUMBER][TAG_NUMBER];
};

#endif