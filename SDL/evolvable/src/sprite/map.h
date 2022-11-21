#ifndef MAP_H_
#define MAP_H_

#include <ostream>
#include <SDL.h>
#include "../box.h"

class Map {
public:
	~Map();
	void init(SDL_Texture* _backgroundImg, SDL_Texture* _whiteTile, SDL_Texture* _blueTile);
	void makeMap(SDL_Point _mapsize);

private:
	SDL_Texture* backgroundImg;
	SDL_Texture* whiteTile;
	SDL_Texture* blueTile;

	bool map[100][100];
	SDL_Point mapSize;
	SDL_Point tileNum;
};

#endif