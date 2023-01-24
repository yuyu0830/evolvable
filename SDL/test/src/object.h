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
#include "graphicManager.h"

#include "sprite/graphic.h"

class Object {
public:
	//void createObject(int x, int y, type _type);
	void load(type _type);

	void draw();
	virtual void update() = 0;

	Object* getNextPtr();
	Object* getPriviousPtr();
	Object* getLastPtr();
	
	void setNextPtr(Object* ptr);
	void setPriviousPtr(Object* ptr);
	void addLastPtr(Object* ptr);

	SDL_FPoint getCenterPoint();

	void setPtrNull();

	Object(int x, int y, type _type);
	virtual ~Object();

	Position position;
	Size size;

protected:
	Graphic* graphic[MAX_GRAPHIC_NUMBER];
	Object* nextPtr = NULL;
	Object* priviousPtr = NULL;

	type objType;

	int objNum; //오브젝트 넘버링
	int graphicAmount; //그래픽 개수
	int graphicFrameNum[MAX_GRAPHIC_NUMBER]; //n번째 그래픽의 현재 프레임 개수

	static int staticObjNum;
};

#endif