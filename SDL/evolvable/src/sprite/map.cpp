#include "map.h"

Map::~Map() {
	SDL_DestroyTexture(backgroundImg);
	SDL_DestroyTexture(whiteTile);
	SDL_DestroyTexture(blueTile);
	printf("Map destroy Complete!\n");
}

void Map::init() {
	SDL_QueryTexture(backgroundImg, NULL, NULL, &mapSize.x, &mapSize.y);
	tileSize = { (int)((mapSize.x + 15) / 45), (int)((mapSize.y + 26) / 52) };
	cameraPos = {0, 0};
}

void Map::makeMap() {
	for (int i = 0; i <= tileSize.x; i++) {
		for (int j = 0; j <= tileSize.y; j++) {
			if (i == 0 || j == 0 || i >= tileSize.x - 1 || j >= tileSize.y - 1) map[i][j] = 1;
			else {
				int a = rand() % 10;
				if (a > 0) map[i][j] = 0;
				else map[i][j] = 1;
			}
		}
	}
}

bool Map::collisionCheck(SDL_FPoint pos, float radius) {
	int tileX = (pos.x + 30) / 45, tileY, tmp;

	if (tileX % 2 == 0) tmp = 0;
	else tmp = 26;

	tileY = (pos.y + tmp) / 52;

	if (map[tileX][tileY]) {
		float lenX = (tileX * 45 - cameraPos.x) - pos.x;
		float lenY = (tileY * 52 + tmp - cameraPos.y) - pos.y;
		float len = sqrt(lenX * lenX + lenY * lenY);
		if (len < 26 + radius) printf("!");
	}
	//(pos.x + 30) % 45 < 15;
	
	return false;
}

void Map::update(SDL_FPoint playerPos, SDL_FPoint* playerInscreenPos) {
	if (playerPos.x < WINDOW_WIDTH / 2) {
		cameraPos.x = 0;
		playerInscreenPos->x = playerPos.x;
	}
	else if (playerPos.x > mapSize.x - (WINDOW_WIDTH / 2)) {
		cameraPos.x = mapSize.x - WINDOW_WIDTH;
		playerInscreenPos->x = playerPos.x - (mapSize.x - WINDOW_WIDTH);
	}
	else {
		cameraPos.x = playerPos.x - (WINDOW_WIDTH / 2);
		playerInscreenPos->x = WINDOW_WIDTH / 2;
	}

	if (playerPos.y < WINDOW_HEIGHT / 2) {
		cameraPos.y = 0;
		playerInscreenPos->y = playerPos.y;
	}
	else if (playerPos.y > mapSize.y - (WINDOW_HEIGHT / 2)) {
		cameraPos.y = mapSize.y - WINDOW_HEIGHT;
		playerInscreenPos->y = playerPos.y - (mapSize.y - WINDOW_HEIGHT);
	}
	else {
		cameraPos.y = playerPos.y - (WINDOW_HEIGHT / 2);
		playerInscreenPos->y = WINDOW_HEIGHT / 2;
	}
}

void Map::draw(SDL_Renderer* renderer) {
	drawTextureA(renderer, { (int)cameraPos.x, (int)cameraPos.y, WINDOW_WIDTH, WINDOW_HEIGHT }, 0, 0, backgroundImg);
	short startX = (int)((cameraPos.x + 15) / 45), endX = (int)((cameraPos.x + WINDOW_WIDTH + 59) / 45);
	short startY = (int)(cameraPos.y / 52), endY = (int)((cameraPos.y + WINDOW_HEIGHT + 51) / 52);
	//printf("%d, %d,   %d, %d\n", startX, endX, startY, endY);
	for (int i = startX; i <= endX; i++) {
		for (int j = startY; j <= endY; j++) {
			int tmp = 0;
			if (i % 2 == 0) tmp = -26;
			else tmp = 0;
			
			if (map[i][j]) drawTexture(renderer, (int)(i * 45 - 30 - cameraPos.x), (int)(j * 52 + tmp - cameraPos.y), blueTile);
			else drawTexture(renderer, (int)(i * 45 - 30 - cameraPos.x), (int)(j * 52 + tmp - cameraPos.y), whiteTile);
		}
	}
}