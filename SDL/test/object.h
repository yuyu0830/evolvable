#pragma once
#include <SDL_image.h>

class Object {
public:
	Vector2 pos;
	int w, h;
	float speed;

	SDL_Texture* image = NULL;

	Object() {}

	void init(Vector2 _pos, float _speed, SDL_Texture* _image);
	void move(Vector2 _des);
	void objDraw(float dir = 0);
};