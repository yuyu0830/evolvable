#include "object.h"

int Object::staticObjectNumber = 0;

void Object::draw() {
	SDL_FPoint point = { position.getX(), position.getY()};
	graphic->draw(point);
}

SDL_FPoint Object::getCenterFPoint() {
	return { position.getX() - size.w / 2, position.getY() - size.h / 2 };
}

SDL_Point Object::getCenterPoint() {
	return { (int) position.getX() - size.w / 2, (int) position.getY() - size.h / 2 };
}

Object::~Object() {
	graphic = NULL;
}