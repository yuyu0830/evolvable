#include "player.h"

void Player::load(SDL_Renderer* renderer, const char* fileDir, ObjectData data, UnitData udata) {
	//texture = loadTexture(renderer, fileDir);

	strcpy_s(name, data.name);
	tag = data.tag;
	unitNum = data.unitNum;
	//SDL_QueryTexture(texture, NULL, NULL, &size.width, &size.height);

	invincible = udata.invincible;
	atk = udata.atk;
	maxHP = udata.maxHP;
	curHP = udata.curHP;
	speed = udata.speed;
}

//void Player::update(Input* input) {
//	if (input->keys[SDL_SCANCODE_W]) {
//		position.move(180.f, speed);
//	}
//	if (input->keys[SDL_SCANCODE_S]) {
//		position.move(0.f, speed);
//	}
//	if (input->keys[SDL_SCANCODE_A]) {
//		position.move(90.f, speed);
//	}
//	if (input->keys[SDL_SCANCODE_D]) {
//		position.move(270.f, speed);
//	}
//}

//void Player::draw(SDL_Renderer* renderer) {
//	SDL_FPoint pos = position.get();
//	drawTexture(renderer, (int) (pos.x - size.width / 2), (int) (pos.y - size.height / 2), texture);
//}
