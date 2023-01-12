#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include <new>

#include <SDL_Image.h>
#include <SDL_ttf.h>

#include "util.h"
#include "Position.h"
#include "collider.h"
#include "input.h"

#include "sprite/graphic.h"

class Object {
public:
	static Object* createObject(int x, int y, type _type);
	void load(type _type);

	void draw();
	void update();

	Object* getNextPtr();
	Object* getPriviousPtr();
	void setNextPtr(Object* ptr);
	void setPriviousPtr(Object* ptr);

	void setPtrNull();

	~Object();

	Position position;
	Size size;

protected:
	Graphic* graphic[10];
	Object* nextPtr = NULL;
	Object* priviousPtr = NULL;

	type objType;
	int objNum;
	int graphicNum;

	static int staticObjNum;
};

#endif