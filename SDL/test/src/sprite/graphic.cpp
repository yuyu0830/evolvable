#include "graphic.h"

Graphic::~Graphic() {

}

void Graphic::dataInput(ObjectData data) {
	strcpy_s(name, data.name);
	tag = data.tag;
	unitNum = data.unitNum;
}