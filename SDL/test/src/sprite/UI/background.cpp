#include "background.h"
Background::Background() {
	color = COLOR_WHITE;
	opacity = 100;
	window = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
}

void Background::setColor(SDL_Color _color) {
	color = _color;
}

void Background::setOpacity(int _opacity) {
	opacity = _opacity;
}

void Background::setWindowSize(int width, int height) {
	window = { 0, 0, width, height };
}

void Background::draw() {
	SDL_SetRenderDrawColor(Renderer::getInstance()->getRenderer(), color.r, color.g, color.b, opacity);
	SDL_RenderFillRect(Renderer::getInstance()->getRenderer(), &window);
	SDL_SetRenderDrawColor(Renderer::getInstance()->getRenderer(), 0, 0, 0, 255);
}