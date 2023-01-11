#include "object.h"

void Object::createObject(int x, int y, type _type) {
	position.set(x, y);

}

void Object::load(type _type) {
	switch (_type) {
	case UI_BUTTON:
		Graphic* g;
	}
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
