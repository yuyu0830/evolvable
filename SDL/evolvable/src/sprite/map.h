#ifndef MAP_H_
#define MAP_H_

#include <ostream>
#include <SDL.h>
#include "../box.h"
#include "../draw.h"

class Map {
public:
	~Map();
	void init(SDL_Texture* _backgroundImg, SDL_Texture* _whiteTile, SDL_Texture* _blueTile);
	void makeMap(SDL_Point _mapsize);
	void draw(SDL_Renderer* renderer, SDL_FPoint playerPos);

private:
	SDL_Texture* backgroundImg;
	SDL_Texture* whiteTile;
	SDL_Texture* blueTile;

	bool map[100][100];
	SDL_FPoint cameraPos;
	SDL_Point mapSize;
	SDL_Point tileSize;

	friend class Object;
};

#endif