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
}

void Map::makeMap(SDL_Point _mapSize) {
	mapSize = _mapSize;

}