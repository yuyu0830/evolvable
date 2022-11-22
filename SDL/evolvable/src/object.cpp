#include "object.h"

void Object::init(SDL_Renderer* renderer) {
	player.turret = loadTexture(renderer, "src/image/Player.png");
	player.caterpillar = loadTexture(renderer, "src/image/caterpillar.png");
	player.fireDirImg = loadTexture(renderer, "src/image/aim.png");
	player.bullet.bulletImg = loadTexture(renderer, "src/image/bullet.png");
	player.init({500, 300}, 5.0f, 1.4f);
	
	map.backgroundImg = loadTexture(renderer, "src/image/background.png");
	map.blueTile = loadTexture(renderer, "src/image/tile_blue.png");
	map.whiteTile = loadTexture(renderer, "src/image/tile_white.png");
	map.init();
	map.makeMap();

	printf("All object initialize Complete!\n");
}

void Object::update(Input* input) {
	player.update(input);
	player.bullet.update();
	map.update(player.pos, &player.inScreenPos);
	map.collisionCheck(player.pos, 5.f);
}

void Object::draw(SDL_Renderer* renderer) {
	map.draw(renderer);
	player.draw(renderer);
	player.bullet.draw(renderer, map.cameraPos);
}

