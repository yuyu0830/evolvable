#include "menu.h"

Menu::Menu() {
	scence = 1;
	button[0] = new UI(
		{"button1", TAG_UI, 1},
		{});
}

void Menu::update(Input* input) {

}

void Menu::draw(SDL_Texture* renderer) {

}

void Menu::scenceChange(int nextScence) {

}