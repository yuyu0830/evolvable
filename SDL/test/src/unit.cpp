#include "unit.h"

void Unit::update() {
	pos.x += 1;
	pos.y += 1;
	printf("%s update!\n", data.name);
}

void Unit::draw(SDL_Renderer* renderer) {
	drawTexture(renderer, pos.x, pos.y, texture);
	printf("%s draw!\n", data.name);
}