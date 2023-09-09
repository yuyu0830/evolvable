#include "graphic.h"

void Graphic::load(type _type) {
	switch (_type) {
	case(UI_BUTTON):
		part[0] = PartsManager::load(BUTTON);
		partAmount = 1;
		break;

	case(UI_TILE):
		part[0] = PartsManager::load(TILE);
		partAmount = 1;
		break;
	}
}

void Graphic::draw(SDL_FPoint point) {
	for (int i = 0; i < partAmount; i++) {
		drawTexture(point, part[i]->getRect(), part[i]->getTexture());
	}
}

Graphic::Graphic() {
	partAmount = 0;
	for (int i = 0; i < MAX_PARTS_NUMBER; i++) {
		part[i] = NULL;
	}
}

Graphic::~Graphic() {

}