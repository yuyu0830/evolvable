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
        SDL_FPoint nextMove = { (sin(caterpillarDir / RADIAN) * move) * -1 * speed , cos(caterpillarDir / RADIAN) * move * speed };
        this->collisionCheck(map, nextMove, move);
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
    SDL_RenderDrawPoint(renderer, pos.x, pos.y);
    /*int tmp;
    for (int i = 0; i < 15; i++) {
        SDL_RenderDrawLine(renderer, i * 45 + 26, 0, i * 45 + 26, WINDOW_HEIGHT);
        for (int j = 0; j < 15; j++) {
            if (i % 2 == 0) tmp = 26;
            else tmp = 0;
            SDL_RenderDrawLine(renderer, i * 45 - 19, j * 52 + tmp, i * 45 + 26, j * 52 + tmp);

        }
    }*/

    int tmp = 0;
    if (tilePos.x % 2 == 0) tmp = 1;

    tilePos.x = ((pos.x + 15) / 45);
    tilePos.y = ((pos.y + (tmp * 26)) / 52);
    printf("[%d, %d]\n", tilePos.x, tilePos.y);
    for (int i = -1; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            int tmp2 = 0;
            if (i == 0) tmp2 = 26;
            if (map[tilePos.x + i][tilePos.y + j - tmp]) {
                SDL_RenderDrawLine(renderer, pos.x, pos.y, (tilePos.x + i) * 45, (tilePos.y + j - tmp) * 52 + (tmp * 26) - tmp2);
            }
        }
    }
    if (map[tilePos.x][tilePos.y - 1 - tmp]) {
        SDL_RenderDrawLine(renderer, pos.x, pos.y, (tilePos.x) * 45, (tilePos.y - 1 - tmp) * 52 + (tmp * 26) - 26);
    }

    /*if (map[tilePos.x - 1][tilePos.y - even]) {
        SDL_RenderDrawLine(renderer, pos.x, pos.y, (tilePos.x - 1) * 45, (tilePos.y - even) * 52 + tmp);
    }
    if (map[tilePos.x - 1][tilePos.y - even + 1]) {
        SDL_RenderDrawLine(renderer, pos.x, pos.y, (tilePos.x - 1) * 45, (tilePos.y - even + 1) * 52 + tmp);
    }
    if (map[tilePos.x][tilePos.y - 1]) {
        SDL_RenderDrawLine(renderer, pos.x, pos.y, tilePos.x * 45, (tilePos.y - 1) * 52 + tmp + 26);
    }
    if (map[tilePos.x][tilePos.y]) {
        SDL_RenderDrawLine(renderer, pos.x, pos.y, tilePos.x * 45, tilePos.y * 52 + tmp + 26);
    }
    if (map[tilePos.x][tilePos.y + 1]) {
        SDL_RenderDrawLine(renderer, pos.x, pos.y, tilePos.x * 45, (tilePos.y + 1) * 52 + tmp + 26);
    }
    if (map[tilePos.x + 1][tilePos.y - even]) {
        SDL_RenderDrawLine(renderer, pos.x, pos.y, (tilePos.x + 1) * 45, (tilePos.y - even) * 52 + tmp);
    }
    if (map[tilePos.x + 1][tilePos.y - even + 1]) {
        SDL_RenderDrawLine(renderer, pos.x, pos.y, (tilePos.x + 1) * 45, (tilePos.y - even + 1) * 52 + tmp);
    }*/
}


void Player::collisionCheck(bool map[100][100], SDL_FPoint nextMove, int move) {
    int tmp = 0;
    if (tilePos.x % 2 == 0) tmp = 1;

    tilePos.x = ((pos.x + 15) / 45);
    tilePos.y = ((pos.y + (tmp * 26)) / 52);

    for (int i = -1; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            int tmp2 = 0;
            if (i == 0) tmp2 = 26;
            if (map[tilePos.x + i][tilePos.y + j - tmp]) {
                float len = sqrt(pow(pos.x - (tilePos.x + i) * 45, 2) + pow(pos.y - ((tilePos.y + j - tmp) * 52 + (tmp * 26) - tmp2), 2));
                if (len <= 46.f) {
                    //printf("[%d, %d]", i, j);
                }
            }
        }
    }
    if (map[tilePos.x][tilePos.y - 1 - tmp]) {
        float len = sqrt(pow(pos.x - (tilePos.x) * 45, 2) + pow(pos.y - ((tilePos.y - 1 - tmp) * 52 + (tmp * 26) + 26), 2));
        if (len <= 46.f) {
            printf("[%d, %d]", 0, -1);
        }
    }
    /*tilePos.x = ((pos.x + nextMove.x + 15) / 45);
    int tmp = 0;
    if (tilePos.x % 2 == 0) tmp = -26;
    tilePos.y = ((pos.y + nextMove.y - tmp) / 52);
    
    bool even = false;
    if (tilePos.x % 2 == 0) even = true;

    float dir;
    if (move < 0) dir = caterpillarDir;
    else dir = ((int)caterpillarDir + 180) % 360;
    printf("%d, %d, %.2f", tilePos.x, tilePos.y, dir);
    bool bx = true, by = true;

    if (dir > 270 || dir < 90) {
        if (map[tilePos.x][tilePos.y - 1]) {
            float x = pow(pos.x - (tilePos.x * 45)) + pow(pos.y - ((tilePos.y - 1) * 52 + tmp + 26));
            if (x <= 2120) {
                printf("up!!  ");
            }
        }
    }
    else if (map[tilePos.x][tilePos.y + 1]) {
        float x = pow(pos.x - (tilePos.x * 45)) + pow(pos.y - ((tilePos.y + 1) * 52 + tmp + 26));
        if (x <= 2120) {
            printf("down!!  ");
        }
    }

    if (dir > 330 || dir < 150) {
        if (map[tilePos.x + 1][tilePos.y - even]) {
            float x = pow(pos.x - ((tilePos.x + 1) * 45)) + pow(pos.y - ((tilePos.y - even) * 52 + tmp));
            if (x <= 2120) {
                printf("right up!!  ");
            }
        }
    }
    else if (map[tilePos.x - 1][tilePos.y + 1 - even]) {
        float x = pow(pos.x - ((tilePos.x - 1) * 45)) + pow(pos.y - ((tilePos.y + 1 - even) * 52 + tmp));
        if (x <= 2120) {
            printf("left down!!  ");
        }
    }

    if (dir > 210 || dir < 30) {
        if (map[tilePos.x - 1][tilePos.y - even]) {
            float x = pow(pos.x - ((tilePos.x - 1) * 45)) + pow(pos.y - ((tilePos.y - even) * 52 + tmp));
            if (x <= 2120) {
                printf("left up!!  ");
            }
        }
    }
    else if (map[tilePos.x + 1][tilePos.y + 1 - even]) {
        float x = pow(pos.x - ((tilePos.x + 1) * 45)) + pow(pos.y - ((tilePos.y + 1- even) * 52 + tmp));
        if (x <= 2120) {
            printf("right down!!  ");

        }
    }
    printf("\n");*/
    pos.x += nextMove.x;
    pos.y += nextMove.y;
}