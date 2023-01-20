#include "tile.h"

int Tile::staticTileNum;

void Tile::update() {
	;
}

Tile::~Tile() {
	printf("Tile %d 소멸자 시작!\n", tileNum);
	printf("Tile %d 소멸자 끝!\n", tileNum);
}