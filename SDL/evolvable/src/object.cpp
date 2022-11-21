#include "object.h"

void Object::init(SDL_Renderer* renderer) {
	SDL_Texture* tmpTexture1 = NULL;
	SDL_Texture* tmpTexture2 = NULL;
	SDL_Texture* tmpTexture3 = NULL;
	SDL_Texture* tmpTexture4 = NULL;

	tmpTexture1 = loadTexture(renderer, "src/image/Player.png");
	tmpTexture2 = loadTexture(renderer, "src/image/caterpillar.png");
	tmpTexture3 = loadTexture(renderer, "src/image/aim.png");
	tmpTexture4 = loadTexture(renderer, "src/image/bullet.png");
	player.init({500, 300}, 5.0f, 1.4f, tmpTexture1, tmpTexture2, tmpTexture3, tmpTexture4);

	map.init(loadTexture(renderer, "src/image/background.png"), loadTexture(renderer, "src/image/tile_white.png"), loadTexture(renderer, "src/image/tile_blue.png"));

	player.mapSizePoint(&map.mapSize);

	SDL_DestroyTexture(tmpTexture1);
	SDL_DestroyTexture(tmpTexture2);
	SDL_DestroyTexture(tmpTexture3);
	SDL_DestroyTexture(tmpTexture4);
	printf("All object initialize Complete!\n");
}

void Object::draw(SDL_Renderer* renderer) {
	map.draw(renderer, player.posReturn());
	player.draw(renderer);
}

void Object::update(Input* input) {
	player.update(input);
	player.bullet.update();
	
}