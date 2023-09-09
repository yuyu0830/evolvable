#include "partsManager.h"

SDL_Texture* PartsManager::texture[PARTS_AMOUNT];

PartsManager::PartsManager() {
	for (int i = 0; i < TYPE_AMOUNT; i++) {
		texture[i] = NULL;
	}
}

Parts* PartsManager::load(parts part) {
	Parts* p;
	switch (part) {
	case BUTTON_MOUSE_ON:
		if (texture[part]) {
			texture[part] = loadTexture("Main_button_onMouse");
		}
		break;

	case BUTTON_MOUSE_OFF:
		texture[BUTTON_MOUSE_OFF] = loadTexture("Main_button_default");
		break;


	case TILE_1:
		texture[TILE_1] = loadTexture("Main_tile1");
		break;

	case TILE_2:
		texture[TILE_2] = loadTexture("Main_tile2");
		break;

	case TILE_3:
		texture[TILE_3] = loadTexture("Main_tile3");
		break;

	case TILE_4:
		texture[TILE_4] = loadTexture("Main_tile4");
		break;

	case TILE_5:
		texture[TILE_5] = loadTexture("Main_tile5");
		break;
	}
	return p;
}

void PartsManager::unload(parts part) {
	SDL_DestroyTexture(texture[part]);
}

void PartsManager::unloadAll() {
	for (int i = 0; i < PARTS_AMOUNT; i++) {
		SDL_DestroyTexture(texture[i]);
	}
	printf("PartsManager : Texture 삭제 완료!\n");
}

