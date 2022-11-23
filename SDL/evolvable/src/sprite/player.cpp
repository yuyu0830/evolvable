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

void Player::update(Input* input, bool map[100][100]) {
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
        SDL_FPoint nextMove = { pos.x + (sin(caterpillarDir / RADIAN) * move) * -1 * speed , pos.y + cos(caterpillarDir / RADIAN) * move * speed };
        //this->collisionCheck(map, nextMove);
        pos = nextMove;
       /* pos.x += (sin(caterpillarDir / RADIAN) * move) * -1 * speed;
        pos.y += cos(caterpillarDir / RADIAN) * move * speed;*/
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
void Player::draw(SDL_Renderer* renderer, bool map[100][100]) {
    drawTextureAR(renderer, caterpillarRect, (int)(inScreenPos.x - w / 2), (int)(inScreenPos.y - h / 2), caterpillarDir, caterpillar);
    drawTexture(renderer, (int)(inScreenPos.x - w / 2), (int)(inScreenPos.y - h / 2) , turret);
    drawTextureR(renderer, (int)(inScreenPos.x - fw / 2), (int)(inScreenPos.y - fh / 2), fireDir, fireDirImg);
    int tmp;
    for (int i = 0; i < 15; i++) {
        SDL_RenderDrawLine(renderer, i * 45, 0, i * 45, WINDOW_HEIGHT);
        for (int j = 0; j < 15; j++) {
            if (i % 2 == 0) tmp = 0;

            SDL_RenderDrawLine(renderer, i * 45, 0, i * 45, WINDOW_HEIGHT);
        }
    }
    
    int tileX = ((pos.x + 30) / 45);
    tmp = -26;
    if (tileX % 2 != 0) tmp = 0;
    int tileY = ((pos.y - tmp) / 52);
    printf("%d, %d\n", tileX, tileY);
    if (tileX > 0) {
        if (map[tileX - 1][tileY]) {
            SDL_RenderDrawLine(renderer, pos.x, pos.y, (tileX - 1) * 45, tileY * 52 + tmp);
            //printf(" 1");
        }
        if (tileY < 100) {
            if (map[tileX - 1][tileY + 1]) {
                SDL_RenderDrawLine(renderer, pos.x, pos.y, (tileX - 1) * 45, (tileY + 1) * 52 + tmp);
                //printf(" 2");
            }
        }
    }
    if (map[tileX][tileY]) {
        SDL_RenderDrawLine(renderer, pos.x, pos.y, tileX * 45, tileY * 52 + tmp + 26);
        //printf(" 3");
    }
    if (tileY < 100) {
        if (map[tileX][tileY + 1]) {
            SDL_RenderDrawLine(renderer, pos.x, pos.y, tileX * 45, (tileY + 1) * 52 + tmp + 26);
            //printf(" 4");
        }
    }
    if (tileY > 0) {
        if (map[tileX][tileY - 1]) {
            SDL_RenderDrawLine(renderer, pos.x, pos.y, tileX * 45, (tileY - 1) * 52 + tmp + 26);
            //printf(" 5");
        }
    }
    if (tileX < 100) {
        if (map[tileX + 1][tileY]) {
            SDL_RenderDrawLine(renderer, pos.x, pos.y, (tileX + 1) * 45, tileY * 52 + tmp);
            //printf("6");
        }
        if (tileY < 100) {
            if (map[tileX + 1][tileY + 1]) {
                SDL_RenderDrawLine(renderer, pos.x, pos.y, (tileX + 1) * 45, (tileY + 1) * 52 + tmp);
                //printf("7");
            }
        }
    }
    //printf("\n");
}


bool Player::collisionCheck(bool map[100][100], SDL_FPoint nextMove) {


    return false;
}