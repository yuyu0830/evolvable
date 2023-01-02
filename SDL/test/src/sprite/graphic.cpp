#include "graphic.h"
Graphic::~Graphic() {
	SDL_DestroyTexture(texture);
}

void Graphic::update(Input* input) {

}

void Graphic::draw(SDL_Renderer* renderer) {
	SDL_FPoint pos = position.get();
	drawTexture(renderer, (int)(pos.x - size.width / 2), (int)(pos.y - size.height / 2), texture);
}