#include "player.h"

Player::~Player() {
	SDL_DestroyTexture(fireDirImg);
	SDL_DestroyTexture(caterpillar);
	SDL_DestroyTexture(turret);
}

void Player::init(SDL_FPoint _pos, float _speed, float _rotateSpeed) {
    strcpy_s(name, "Player");    
    pos = _pos;
    speed = _speed;
    rotateSpeed = _rotateSpeed;

    caterpillarRect = { 0, 0, 40, 40 };

    fireDir = 0.0f;
    caterpillarNum = 0;
    caterpillarDir = 0.0f;

    inScreenPos = _pos;
    SDL_QueryTexture(fireDirImg, NULL, NULL, &fw, &fh);
    SDL_QueryTexture(turret, NULL, NULL, &w, &h);
    printf("%s initialize complete!\n", name);
    bullet.init(name, 2.0f);
}

void Player::update(Input* input) {
    int move = 0;
    if (input->keys[4]) {
        caterpillarDir -= rotateSpeed;
    }
    if (input->keys[7]) {
        caterpillarDir += rotateSpeed;
    }
    if (input->keys[26]) {
        move -= 1;
        caterpillarNum -= 1;
    }
    if (input->keys[22]) {
        move += 1;
        caterpillarNum += 1;
    }

    if (move != 0) {
        if (caterpillarNum >= 3) caterpillarNum -= 3;
        else if (caterpillarNum < 0) caterpillarNum += 3;
        pos.x += (sin(caterpillarDir / RADIAN) * move) * -1 * speed;
        pos.y += cos(caterpillarDir / RADIAN) * move * speed;
    }
    
    if (caterpillarDir >= 360) caterpillarDir -= 360;
    else if (caterpillarDir < 0) caterpillarDir += 360;
    caterpillarRect = { (caterpillarNum / 2) * 40,(caterpillarNum % 2) * 40 , 40, 40 };
    fireDir = atan2(input->mousePos.y - inScreenPos.y, input->mousePos.x - inScreenPos.x) * RADIAN + 90;
    if (fireDir > 360) fireDir -= 360;
    if (input->mouseClick[0] && !input->mouseClicked[0]) {
        bullet.create(fireDir, pos);
        input->mouseClicked[0] = true;
    }
}

//draw
void Player::draw(SDL_Renderer* renderer) {
    drawTextureAR(renderer, caterpillarRect, (int)(inScreenPos.x - w / 2), (int)(inScreenPos.y - h / 2), caterpillarDir, caterpillar);
    drawTexture(renderer, (int)(inScreenPos.x - w / 2), (int)(inScreenPos.y - h / 2) , turret);
    drawTextureR(renderer, (int)(inScreenPos.x - fw / 2), (int)(inScreenPos.y - fh / 2), fireDir, fireDirImg);
}
