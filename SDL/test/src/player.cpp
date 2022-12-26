#include "player.h"

Player::Player(float _speed) {
	speed = _speed;
}

void Player::update(Input* input) {
	if (input->keys[SDL_SCANCODE_W]) {
		pos.y -= speed;
	}
	if (input->keys[SDL_SCANCODE_S]) {
		pos.y += speed;
	}
	if (input->keys[SDL_SCANCODE_A]) {
		pos.x -= speed;
	}
	if (input->keys[SDL_SCANCODE_D]) {
		pos.x += speed;
	}
}

void Player::draw(SDL_Renderer* renderer) {
	drawTexture(renderer, pos.x, pos.y, texture);
}
