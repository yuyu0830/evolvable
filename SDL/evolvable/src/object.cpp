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
	player.init({500, 300}, 1.0f, 1.4f, tmpTexture1, tmpTexture2, tmpTexture3, tmpTexture4);
}

void Object::draw(SDL_Renderer* renderer) {
	player.draw(renderer);
}

void Object::update(Input* input) {
	player.update(input);
	player.bullet.update();
}