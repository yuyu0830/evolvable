#include "map.h"

Map::~Map() {
	SDL_DestroyTexture(backgroundImg);
	SDL_DestroyTexture(whiteTile);
	SDL_DestroyTexture(blueTile);
	printf("Map destroy Complete!\n");
}

void Map::init(SDL_Texture* _backgroundImg, SDL_Texture* _whiteTile, SDL_Texture* _blueTile) {
	backgroundImg = _backgroundImg;
	whiteTile = _whiteTile;
	blueTile = _blueTile;
	
	SDL_QueryTexture(backgroundImg, NULL, NULL, &mapSize.x, &mapSize.y);

	cameraPos = {0, 0};
}

void Map::makeMap(SDL_Point _mapSize) {
	mapSize = _mapSize;
	tileSize = { (int)((mapSize.x - 30) / 45), (int)((mapSize.y - 26) / 52) };
	int size;
	for (int i = 0; i < tileSize.x; i++) {
		for (int j = 0; j < tileSize.y; j++) {
			if (i == 0 || j == 0) map[i][j] = 1;
			else map[i][j] = 0;
		}
	}
}

void Map::draw(SDL_Renderer* renderer, SDL_FPoint playerPos) {
	cameraPos = { playerPos.x - WINDOW_WIDTH / 2, playerPos.y - WINDOW_HEIGHT / 2 };
	drawTextureA(renderer, { (int)cameraPos.x, (int)cameraPos.y, WINDOW_WIDTH, WINDOW_HEIGHT }, 0, 0, backgroundImg);
}
