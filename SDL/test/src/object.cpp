#include "object.h"

int Object::staticObjNum = 0;

Object::Object(int x, int y, type _type) {
	position.set(x, y);
	objType = _type;
	setPtrNull();
	load(_type);
	objNum = staticObjNum++;
}

//void Object::createObject(int x, int y, type _type) {
//	position.set(x, y);
//	setPtrNull();
//	load(_type);
//}

void Object::load(type _type) {
	switch (_type) {
	case(UI_BUTTON):
		graphic[0] = GraphicManager::getGraphic(BUTTON);
		graphicNum = 1;
		break;
	case(UI_TILE):
		graphic[0] = GraphicManager::getGraphic(TILE);
		graphicNum = 1;
		break;
	}
	printf("%p\n", graphic[0]);
	size.width = graphic[0]->size.width;
	size.height = graphic[0]->size.height;
}

void Object::draw() {
	for (int i = 0; i < graphicNum; i++) {
		drawTexture(Position::add(getCenterPoint(), graphic[i]->position.get()), graphic[i]->getTexture());
	}
}

Object* Object::getNextPtr() {
	return nextPtr;
}

Object* Object::getPriviousPtr() {
	return priviousPtr;
}

Object* Object::getLastPtr() {
	if (nextPtr) {
		return getNextPtr()->getLastPtr();
	}
	else {
		return this;
	}
	//미완성
}

void Object::setNextPtr(Object* ptr) {
	nextPtr = ptr;
}

void Object::setPriviousPtr(Object* ptr) {
	priviousPtr = ptr;
}

void Object::addLastPtr(Object* ptr) {
	if (nextPtr) {
		getNextPtr()->addLastPtr(ptr);
	}
	else {
		nextPtr = ptr;
	}
}

SDL_FPoint Object::getCenterPoint() {
	return { position.getX() - size.width / 2, position.getY() - size.height / 2 };
}

void Object::setPtrNull() {
	for (int i = 0; i < MAX_GRAPHIC_NUMBER; i++) {
		graphic[i] = NULL;
	}
}

Object::~Object() {
	printf("    Object %d 소멸자 시작!\n", objNum);
	for (int i = 0; i < graphicNum; i++) {
		delete graphic[i];
	}
	delete nextPtr;
	printf("    Object %d 소멸자 끝!\n", objNum);
}