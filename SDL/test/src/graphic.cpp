#include "graphic.h"

void Graphic::load(objectData _data, SDL_Renderer* renderer, const char* file, SDL_Rect dst) {
	data = _data;
	texture = loadTexture(renderer, file);
	pos = dst;
}