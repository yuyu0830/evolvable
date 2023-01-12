#include "object.h"

Object* Object::createObject(int x, int y, type _type) {
	Object* o = new Object();

	o->position.set(x, y);
	o->setPtrNull();
	o->load(_type);
	
	return o;
}

void Object::load(type _type) {
	switch (_type) {
	case UI_BUTTON:
		
	}
}

void Object::draw() {
	drawTexture(position.get(), graphic[0]->getTexture());
}

void Object::update() {
	;
}



Object* Object::getNextPtr() {
	return nextPtr;
}

Object* Object::getPriviousPtr() {
	return priviousPtr;
}

void Object::setNextPtr(Object* ptr) {
	nextPtr = ptr;
}

void Object::setPriviousPtr(Object* ptr) {
	priviousPtr = ptr;
}

void Object::setPtrNull() {
	for (int i = 0; i < 10; i++) {
		graphic[i] = NULL;
	}
}

Object::~Object() {
	delete[] graphic;
}