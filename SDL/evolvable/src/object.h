#ifndef OBJECT_H_
#define OBJECT_H_

#include <SDL.h>
#include <SDL_image.h>

#include "draw.h"
#include "sprite/bullet.h"
#include "sprite/map.h"
#include "sprite/player.h"

class Object {
public:
	void init(SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer);
	void update(Input* input);

private:
	Player player;
	Map map;

};

#endif