#include "object.h"

int Object::staticObjNum = 0;

Object::Object(int x, int y, type _type) {
	position.set(x, y);
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
	case UI_BUTTON:
		char tmp[5][20] = {
			"Main_button_default",
			"Main_button_onMouse",
			"",
			"",
			""
		};
		Graphic* g1 = new Graphic();

		g1 = Graphic::create(0, 0, tmp, 2);
		graphic[0] = g1;
		graphicNum = 1;

		size.width = graphic[0]->size.width;
		size.height = graphic[0]->size.height;

		g1 = NULL;
		delete g1;
	}
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

void Object::setNextPtr(Object* ptr) {
	nextPtr = ptr;
}

void Object::setPriviousPtr(Object* ptr) {
	priviousPtr = ptr;
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
	printf("    Object %d ¼Ò¸êÀÚ ½ÃÀÛ!\n", objNum);
	for (int i = 0; i < graphicNum; i++) {
		delete graphic[i];
	}
	printf("    Object %d ¼Ò¸êÀÚ ³¡!\n", objNum);
	
}