#include "tile.h"

int Tile::staticTileNum;

void Tile::update() {
	;
}

Tile::~Tile() {
	printf("Tile %d �Ҹ��� ����!\n", tileNum);
	printf("Tile %d �Ҹ��� ��!\n", tileNum);
}