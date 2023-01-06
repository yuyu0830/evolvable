#include "position.h"

SDL_FPoint Position::get() {
	return { x, y };
}

void Position::set(float _x, float _y) {
	x = _x;
	y = _y;
}

void Position::set(int _x, int _y) {
	x = (float) _x;
	y = (float) _y;
}

void Position::set(SDL_Point pos) {
	x = (float)pos.x;
	y = (float)pos.y;
}

void Position::move(float angle, float speed) {
	x += sin(angle / RADIAN) * -1 * speed;
    y += cos(angle / RADIAN) * speed ;
}