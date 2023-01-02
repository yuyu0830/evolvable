#include "background.h"

void Background::load(SDL_Renderer* renderer, const char* fileDir) {
	texture = loadTexture(renderer, fileDir);

	strcpy_s(name, "background");
	tag = TAG_BACKGROUND;
	unitNum = 0;
	SDL_QueryTexture(texture, NULL, NULL, &size.width, &size.height);
	printf("%d, %d\n", size.width, size.height);
}

void Background::draw(SDL_Renderer* renderer) {
	drawTextureOption(renderer, { (size.width - WINDOW_WIDTH) / 2, (size.height - WINDOW_HEIGHT) / 2, WINDOW_WIDTH, WINDOW_HEIGHT }, { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT }, texture);
}