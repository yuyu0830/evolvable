#include "graphicManager.h"

Graphic* GraphicManager::graphic[PARTSNUM];

GraphicManager::GraphicManager() {
	for (int i = 0; i < TYPENUM; i++) {
		graphic[i] = NULL;
	}
}

Graphic* GraphicManager::getGraphic(parts part) {
	if (!graphic[part]) {
		loadGraphic(part);
	}
	printf("%p\n", graphic[part]);
	return graphic[part];
}

bool GraphicManager::checkGraphic(parts part) {
	if (graphic[part]) {
		return true;
	}
	else {
		return false;
	}
}


void GraphicManager::loadGraphic(parts part) {
	char fileDir[5][20] = { "", "", "", "", "" };
	switch (part) {
	case BUTTON:
		strcpy_s(fileDir[0], "Main_button_default");
		strcpy_s(fileDir[1], "Main_button_onMouse");

		graphic[BUTTON] = Graphic::create(0, 0, fileDir, 2);
		break;

	case TILE:
		strcpy_s(fileDir[0], "Main_tile1");
		strcpy_s(fileDir[1], "Main_tile2");
		strcpy_s(fileDir[2], "Main_tile3");
		strcpy_s(fileDir[3], "Main_tile4");
		strcpy_s(fileDir[4], "Main_tile5");

		graphic[TILE] = Graphic::create(0, 0, fileDir, 5, true, rand() % 5);
		break;
	}
}

void GraphicManager::loadGraphic(parts part[]) {
	;
}


void GraphicManager::deleteGraphic(parts part) {

}

void GraphicManager::deleteGraphic(parts part[]) {

}


void GraphicManager::deleteAllGraphic() {
	delete[] graphic;
}