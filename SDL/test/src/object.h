#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>

#include <SDL_Image.h>
#include <SDL_ttf.h>

#include "util.h"
#include "Position.h"
#include "collider.h"
#include "input.h"

#include "sprite/graphic.h"

class Object {
public:
	void createObject(int x, int y, type _type);

	void load(type _type);

	Object* getNextPtr();
	Object* getPriviousPtr();
	void setNextPtr(Object* ptr);
	void setPriviousPtr(Object* ptr);

	Position position;
	Size size;

private:
	std::vector<Graphic*> graphic;
	Object* nextPtr = NULL;
	Object* priviousPtr = NULL;

	type objType;
	int objNum;

	static int staticObjNum;
};

#endif