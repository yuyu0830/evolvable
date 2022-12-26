#include "unit.h"

void Unit::update(Input* input) {

}

void Unit::draw(SDL_Renderer* renderer) {
	drawTexture(renderer, pos.x, pos.y, texture);
}