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
	switch (part) {
	case BUTTON:
	case BUTTON_MOUSE_ON:
	case BUTTON_MOUSE_OFF:
		texture[BUTTON_MOUSE_ON] = loadTexture("Main_button_onMouse");
		texture[BUTTON_MOUSE_OFF] = loadTexture("Main_button_default");
		break;

	case TILE:
	case TILE_1:
	case TILE_2:
	case TILE_3:
	case TILE_4:
	case TILE_5:
		texture[TILE_1] = loadTexture("Main_tile1");
		texture[TILE_2] = loadTexture("Main_tile2");
		texture[TILE_3] = loadTexture("Main_tile3");
		texture[TILE_4] = loadTexture("Main_tile4");
		texture[TILE_5] = loadTexture("Main_tile5");
		break;
	}
}

void GraphicManager::unload(parts part) {
	switch (part) {
	case BUTTON:
	case BUTTON_MOUSE_ON:
	case BUTTON_MOUSE_OFF:
		SDL_DestroyTexture(texture[BUTTON_MOUSE_ON]);
		SDL_DestroyTexture(texture[BUTTON_MOUSE_OFF]);
		break;

	case TILE:
	case TILE_1:
	case TILE_2:
	case TILE_3:
	case TILE_4:
	case TILE_5:
		SDL_DestroyTexture(texture[TILE_1]);
		SDL_DestroyTexture(texture[TILE_2]);
		SDL_DestroyTexture(texture[TILE_3]);
		SDL_DestroyTexture(texture[TILE_4]);
		SDL_DestroyTexture(texture[TILE_5]);
		break;
	}
}


void GraphicManager::unloadAll() {
	for (int i = 0; i < PARTSNUM; i++) {
		SDL_DestroyTexture(texture[i]);
	}
	printf("GraphicManager : Texture 삭제 완료!\n");
}