#include "graphic.h"

Graphic* Graphic::getNextPtr() {
	return nextPtr;
}

Graphic* Graphic::getPriviousPtr() {
	return priviousPtr;
}

void Graphic::setNextPtr(Graphic* ptr) {
	nextPtr = ptr;
}

void Graphic::setPriviousPtr(Graphic* ptr) {
	priviousPtr = ptr;
}
