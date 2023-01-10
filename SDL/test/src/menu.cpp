#include "menu.h"

Menu::Menu() {
	scence = 1;
	tile[0] = loadTexture("src/image/Main_tile1.png");
	tile[1] = loadTexture("src/image/Main_tile2.png");
	tile[2] = loadTexture("src/image/Main_tile3.png");
	tile[3] = loadTexture("src/image/Main_tile4.png");
	tile[4] = loadTexture("src/image/Main_tile5.png");
}

void Menu::update() {

}

void Menu::draw() {
	drawBackgroundColor(COLOR_WHITE);
	drawTexture(100, 100, tile[2]);
	drawTexture(100, 326, tile[3]);
	drawTexture(299, 213, tile[4]);
}

void Menu::scenceChange(menuScene scene) {

}

void Menu::drawBackgroundColor(SDL_Color color) {
	SDL_SetRenderDrawColor(Renderer::getInstance()->getRenderer(), color.r, color.g, color.b, 255);

	SDL_Rect r = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	SDL_RenderFillRect(Renderer::getInstance()->getRenderer(), &r);

	SDL_SetRenderDrawColor(Renderer::getInstance()->getRenderer(), 0, 0, 0, 255);
}