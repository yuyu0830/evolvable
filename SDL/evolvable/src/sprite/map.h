#ifndef MAP_H_
#define MAP_H_

#include <ostream>
#include <SDL.h>
#include "../box.h"
#include "../draw.h"

class Map {
public:
	~Map();
	void init();
	void makeMap();
	bool collisionCheck(SDL_Renderer* renderer, SDL_FPoint pos, float radius);

	void update(SDL_FPoint playerPos, SDL_FPoint* playerInscreenPos);
	void draw(SDL_Renderer* renderer);

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