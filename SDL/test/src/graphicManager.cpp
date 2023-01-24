#include "graphicManager.h"

SDL_Texture* GraphicManager::texture[PARTSNUM];

GraphicManager::GraphicManager() {
	for (int i = 0; i < TYPENUM; i++) {
		texture[i] = NULL;
	}
}

GraphicManager::~GraphicManager() {
	printf("GraphicManager 소멸자\n");
}

SDL_Texture* GraphicManager::get(parts part) {
	if (!texture[part]) {
		load(part);
	}
	return texture[part];
}

bool GraphicManager::check(parts part) {
	if (texture[part]) {
		return true;
	}
	else {
		return false;
	}
}


void GraphicManager::load(parts part) {
	char fileDir[5][20] = { "", "", "", "", "" };
	switch (part) {
	case BUTTON:
	case BUTTON_MOUSE_ON:
	case BUTTON_MOUSE_OFF:
		texture[BUTTON_MOUSE_ON] = loadTexture("Main_button_onMouse");
		texture[BUTTON_MOUSE_OFF] = loadTexture("Main_button_default");
		break;

	case TILE:
		texture[TILE_1] = loadTexture("Main_tile1");
		texture[TILE_2] = loadTexture("Main_tile2");
		texture[TILE_3] = loadTexture("Main_tile3");
		texture[TILE_4] = loadTexture("Main_tile4");
		texture[TILE_5] = loadTexture("Main_tile5");
		break;
	}
}

void GraphicManager::load(parts part[]) {
	;
}


void GraphicManager::deleteOne(parts part) {

}

void GraphicManager::deleteOne(parts part[]) {

}


void GraphicManager::deleteAll() {
	for (int i = 0; i < PARTSNUM; i++) {
		SDL_DestroyTexture(texture[i]);
	}
	printf("GraphicManager : Texture 삭제 완료!\n");
}