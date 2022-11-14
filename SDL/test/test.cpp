#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include "box.h"
#include "player.h"
#include "object.h"
#include "bullet.h"
#include "camera.h"
#include "OBJManager.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

//handler
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
//main::function
bool OutOfMap(Vector2 pos, int w, int h);
bool initAll();
bool closeAll();
void update();
void draw();
void inputCal(SDL_Event e);
void drawTexture(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture);
void drawTextureR(SDL_Renderer* renderer, int x, int y, float angle, SDL_Texture* texture);
void drawTextureA(SDL_Renderer* renderer, SDL_Rect src, int x, int y, SDL_Texture* texture);
void drawTextureAR(SDL_Renderer* renderer, SDL_Rect src, int x, int y, float angle, SDL_Texture* texture);
SDL_Texture* loadTexture(const char* file);

//global var
bool keys[255] = { 0, };
bool specialKeys[10] = { 0, };
bool developerMode = true;
bool moveMode = true;
Mouse mouse;
OBJManager obj;
SDL_Texture* bullet1 = NULL;
Camera camera;
vector<int> activeBulletNum;

int main(int argv, char** args) {
    srand(time(NULL));
    bool running = initAll();
    obj.player.init(Vector2(500, 300), 1.5f, loadTexture("src/Player.png"), loadTexture("src/aim.png"), loadTexture("src/caterpillar.png"));
    bullet1 = loadTexture("src/bullet.png");
    camera.init(loadTexture("src/background.png"), loadTexture("src/walls.png"));
    camera.makeMap();
    if (running) {
        SDL_Event event;
        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) running = false;
                else inputCal(event);
            }
            update();
            draw();
        }
    }
    else {
        printf("Running failed..\n");
    }
    closeAll();
    return 0;
}


//###########################################################################
//#################################main######################################
void update() {
    obj.player.update();
    camera.update();
    if (mouse.click[0] && !mouse.clicked[0]) {
        mouse.clicked[0] = true;
        obj.BulletCreate();
    }
    obj.BulletUpdate();
}

void inputCal(SDL_Event event) {
    switch (event.type) {
    case SDL_KEYDOWN:
        //printf("%d\n", event.key.keysym.scancode);
        keys[event.key.keysym.scancode] = true;
        if (event.key.keysym.scancode == 60) {
            developerMode = !developerMode;
        }
        if (event.key.keysym.scancode == 59) {
            moveMode = !moveMode;
        }
        break;
    case SDL_KEYUP:
        keys[event.key.keysym.scancode] = false;
        break;
    case SDL_MOUSEMOTION:
        mouse.pos.x = event.motion.x;
        mouse.pos.y = event.motion.y;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
            mouse.click[0] = true;
        }
        else if (event.button.button == SDL_BUTTON_RIGHT) {
            mouse.click[1] = true;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT) {
            mouse.click[0] = false;
            mouse.clicked[0] = false;
        }
        else if (event.button.button == SDL_BUTTON_RIGHT) {
            mouse.click[1] = false;
            mouse.clicked[1] = false;
        }
        break;
    }
}

bool initAll() {
    //initialize video
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Video Initialize failed! error code : %s\n", (SDL_GetError()));
        return 0;
    }

    //initialize window
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (window == 0) {
        printf("Create window failed! error code : %s\n", (SDL_GetError()));
        return 0;
    }

    //initialize renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == 0)
    {
        printf("Renderer Initialize failed! error code : %s\n", (SDL_GetError()));
        return (0);
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        printf("Image initialize failed! error code : %s\n", (IMG_GetError()));
        return 0;
    }

    if (TTF_Init() != 0) {
        printf("Font initialize failed! error code : %s\n", TTF_GetError());
        return 0;
    }

    font = TTF_OpenFont("HBIOS-SYS.ttf", 32);
    if (font == NULL) {
        printf("Failed to load font!\n");
        return 0;
    }

    return 1;
}

bool closeAll() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(bullet1);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 1;
}

//draw
void draw() {
    SDL_RenderClear(renderer);
    camera.drawBackground();
    camera.drawWalls();
    obj.BulletDraw();
    obj.player.draw();
    if (developerMode) {
        camera.drawDeveloperMode();
    }
    SDL_RenderPresent(renderer);
}


//###########################################################################
//#################################camera####################################
void Camera::init(SDL_Texture* _backgroundIMG, SDL_Texture* _wall) {
    wall = _wall;
    backgroundIMG = _backgroundIMG;
    SDL_QueryTexture(_backgroundIMG, NULL, NULL, &imgWidth, &imgHeight);
    pos = { 0, 0 };
}

void Camera::update() {
    if (obj.player.pos.x < WINDOW_WIDTH / 2) pos.x = 0;
    else if (obj.player.pos.x > imgWidth - WINDOW_WIDTH / 2) pos.x = imgWidth - WINDOW_WIDTH;
    else pos.x = obj.player.pos.x - WINDOW_WIDTH / 2;

    if (obj.player.pos.y < WINDOW_HEIGHT / 2) pos.y = 0;
    else if (obj.player.pos.y > imgWidth - WINDOW_HEIGHT / 2) pos.y = imgWidth - WINDOW_HEIGHT;
    else pos.y = obj.player.pos.y - WINDOW_HEIGHT / 2;
}

void Camera::makeMap() {
    bool tempMap[77][77] = {0, };
    for (int i = 1; i < 76; i++) {
        for (int j = 1; j < 76; j++) {
            if (i == 1 || j == 1 || i == 75 || j == 75) tempMap[i][j] = true;
            else {
                int a = rand() % 10;
                if (a > 1) tempMap[i][j] = false;
                else tempMap[i][j] = true;
            }
        }
    }
    for (int i = 1; i < 76; i++) {
        for (int j = 1; j < 76; j++) {
            if (tempMap[i][j]) {
                if (tempMap[i][j + 1]) {
                    if (tempMap[i][j - 1]) {
                        if (tempMap[i + 1][j]) {
                            if (tempMap[i - 1][j]) map[i-1][j-1] = 17;
                            else map[i-1][j-1] = 15;
                        }
                        else {
                            if (tempMap[i - 1][j]) map[i-1][j-1] = 14;
                            else map[i-1][j-1] = 12;
                        }
                    }
                    else {
                        if (tempMap[i + 1][j]) {
                            if (tempMap[i - 1][j]) map[i-1][j-1] = 16;
                            else map[i-1][j-1] = 7;
                        }
                        else {
                            if (tempMap[i - 1][j]) map[i-1][j-1] = 8;
                            else map[i-1][j-1] = 4;
                        }
                    }
                }
                else {
                    if (tempMap[i][j - 1]) {
                        if (tempMap[i + 1][j]) {
                            if (tempMap[i - 1][j]) map[i-1][j-1] = 13;
                            else map[i-1][j-1] = 6;
                        }
                        else {
                            if (tempMap[i - 1][j]) map[i-1][j-1] = 9;
                            else map[i-1][j-1] = 2;
                        }
                    }
                    else {
                        if (tempMap[i + 1][j]) {
                            if (tempMap[i - 1][j]) map[i-1][j-1] = 11;
                            else map[i-1][j-1] = 3;
                        }
                        else {
                            if (tempMap[i - 1][j]) map[i-1][j-1] = 5;
                            else map[i-1][j-1] = 1;
                        }
                    }
                }
            }
        }
    }
    return;
};

float Camera::wallCheck(float angle) {
    while (angle >= 90.0f) {
        angle -= 90.0f;
    }
    float x = sin(angle / RADIAN) * DIAGONAL_LENGTH;
    float y = cos(angle / RADIAN) * DIAGONAL_LENGTH;
    if (map[(int)((obj.player.pos.x + x) / 40)][(int)((obj.player.pos.y - y) / 40)]) {
        return false;
    }
    if (map[(int)((obj.player.pos.x + y) / 40)][(int)((obj.player.pos.y + x) / 40)]) {
        return false;
    }
    if (map[(int)((obj.player.pos.x - x) / 40)][(int)((obj.player.pos.y + y) / 40)]) {
        return false;
    }
    if (map[(int)((obj.player.pos.x - y) / 40)][(int)((obj.player.pos.y - x) / 40)]) {
        return false;
    }
    return true;


    /*if (map[(int)((obj.player.pos.x + x) / 40)][(int)((obj.player.pos.y - y) / 40)]) {
        if (map[(int)((obj.player.pos.x + x) / 40) - 2][(int)((obj.player.pos.y - y) / 40)]) {

        }
    }
    if (map[(int)((obj.player.pos.x + y) / 40)][(int)((obj.player.pos.y + x) / 40)]) {
        printf("2\n");
    }
    if (map[(int)((obj.player.pos.x - x) / 40)][(int)((obj.player.pos.y + y) / 40)]) {
        printf("3\n");
    }
    if (map[(int)((obj.player.pos.x - y) / 40)][(int)((obj.player.pos.y - x) / 40)]) {
        printf("4\n");
    }
    return true;*/
}

bool Camera::wallCheck(float x, float y) {
    if (map[(int)x / 40][(int)y / 40]) {
        return true;
    }
    return false;
}

//draw
void Camera::drawBackground() {
    SDL_Rect src;
    src.x = pos.x;
    src.y = pos.y;
    src.w = WINDOW_WIDTH;
    src.h = WINDOW_HEIGHT;
    drawTextureA(renderer, src, 0, 0, backgroundIMG);

}

void Camera::drawWalls() {
    SDL_Rect src;
    short startX = pos.x / 40, endX = (pos.x + WINDOW_WIDTH + 39) / 40;
    short startY = pos.y / 40, endY = (pos.y + WINDOW_WIDTH + 39) / 40;
    for (int i = startX; i < endX; i++) {
        for (int j = startY; j < endY; j++) {
            if (map[i][j] != 0) {
                src.x = ((map[i][j] - 1) % 5) * 40; src.y = ((map[i][j] - 1) / 5) * 40;
                src.w = 40; src.h = 40;
                drawTextureA(renderer, src, i * 40 - pos.x, j * 40 - pos.y, wall);
            }
        }
    }
}

void Camera::drawDeveloperMode() {
    char t[100];
    sprintf_s(t, sizeof(t), "x = %.3f  y = %.3f  dir = %.3f  bullet = %d", obj.player.pos.x, obj.player.pos.y, obj.player.caterpillarDir, obj.bulletNum);
    text = TTF_RenderText_Solid(font, t, color);
    texture = SDL_CreateTextureFromSurface(renderer, text);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dst = { 20, 20, texW, texH };
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}


//###########################################################################
//#################################object####################################
void Object::init(Vector2 _pos, float _speed, SDL_Texture* _image) {
    pos = _pos;
    speed = _speed;
    image = _image;
    SDL_QueryTexture(_image, NULL, NULL, &w, &h);
}

void Object::move(Vector2 _des) {
    pos = VecAdd(pos, _des, speed);
}

//draw
void Object::drawObj(float _dir) {
    if (pos.x > camera.pos.x && pos.x < camera.pos.x + WINDOW_WIDTH && pos.y > camera.pos.y && pos.y < camera.pos.y + WINDOW_HEIGHT) {
        if (_dir == 0) {
            drawTexture(renderer, (int)pos.x - (w / 2) - camera.pos.x, (int)pos.y - (h / 2) - camera.pos.y, image);
        }
        else drawTextureR(renderer, (int)pos.x - (w / 2), (int)pos.y - (h / 2), _dir, image);
    }
}


//###########################################################################
//#################################OBJManager################################
void OBJManager::BulletCreate() {
    if (bulletNum < BULLETSIZE) {
        int tmpNum = 0;
        while (bullet[tmpNum].active) { tmpNum++; }
        bullet[tmpNum].active = true;
        bullet[tmpNum].init(player.pos, 3.0f, bullet1);
        float angle = obj.player.dir / RADIAN;
        bullet[tmpNum].dir = Vector2(cos(angle), sin(angle));
        bulletNum++;
    }
}

void OBJManager::BulletUpdate() {
    int sum = 0;
    for (int i = 0; i < BULLETSIZE; i++) {
        if (bullet[i].active) {
            int x = (int)bullet[i].pos.x;
            int y = (int)bullet[i].pos.y;
            bullet[i].move(bullet[i].dir);
            if (OutOfMap(bullet[i].pos, bullet[i].w, bullet[i].h)) {
                bullet[i].active = false;
                printf("bullet %d disabled!\n", i);
                bulletNum--;
            }
            else if ((int)bullet[i].pos.x - x != 0 || (int)bullet[i].pos.y - y != 0) {
                if (camera.map[(int)bullet[i].pos.x / 40][(int)bullet[i].pos.y / 40]) {
                    bullet[i].active = false;
                    printf("bullet %d disabled!\n", i);
                    bulletNum--;
                }
            }
            sum++;
            activeBulletNum.push_back(i);
            if (sum >= bulletNum) return;
        }
    }
}

//draw
void OBJManager::BulletDraw() {
    for (int i : activeBulletNum) {
        bullet[i].drawObj();
    }
    activeBulletNum.clear();
}


//###########################################################################
//#################################Player####################################
void Player::init(Vector2 _pos, float _speed, SDL_Texture* _image, SDL_Texture* _aim, SDL_Texture* _caterpillar){
    pos = _pos;
    speed = _speed;
    image = _image;
    aim = _aim;
    caterpillar = _caterpillar;
    caterpillarNum = 0;
    caterpillarDir = 0.0f;
    inScreenPos = Vector2(0, 0);
    blockX = 0;
    blockY = 0;
    SDL_QueryTexture(_image, NULL, NULL, &w, &h);
}

void Player::move(float moveX, float moveY) {
    for (int i = 0; i < 4; i++) led[i] = 0;
    int a, b, c;
    if (moveX < 0) {
        a = 2, b = 3, c = 0;
    }
    else {
        a = 0, b = 1, c = 1;
    }

    if (camera.wallCheck(vertex[a].x + moveX, vertex[a].y) || camera.wallCheck(vertex[b].x + moveX, vertex[b].y)) {
        led[c] = true;
    }
    else {
        pos.x += moveX;
    }
    

    if (moveY < 0) {
        a = 0, b = 3, c = 2;
    }
    else {
        a = 1, b = 2, c = 3;
    }

    if (camera.wallCheck(vertex[a].x, vertex[a].y + moveY) || camera.wallCheck(vertex[b].x, vertex[b].y + moveY)) {
        led[c] = true;
    }
    else {
        pos.y += moveY;
    }
}

void Player::update() {
    // input Player's moving
    int move = 0;
    if (keys[26]) { // w
        move -= 1;
    }
    if (keys[22]) { // s
        move += 1;
    }
    if (keys[4]) { // a
        if (camera.wallCheck(caterpillarDir - 1.4f)) {
            caterpillarDir -= 1.4f;
        }
        //caterpillarDir = camera.wallCheck(caterpillarDir - 1.4f);
    }
    if (keys[7]) { // d
        if (camera.wallCheck(caterpillarDir + 1.4f)) {
            caterpillarDir += 1.4f;
        }
        //caterpillarDir = camera.wallCheck(caterpillarDir - 1.4f);
    }

    // caterpillar direction
    if (caterpillarDir >= 360) caterpillarDir -= 360;
    else if (caterpillarDir < 0) caterpillarDir += 360;

    // calculate vertax
    float angle = caterpillarDir + 45.0f;
    while (angle >= 90.0f) {
        angle -= 90.0f;
    }
    float x = sin(angle / RADIAN) * DIAGONAL_LENGTH;
    float y = cos(angle / RADIAN) * DIAGONAL_LENGTH;
    vertex[0] = { pos.x + x, pos.y - y };
    vertex[1] = { pos.x + y, pos.y + x };
    vertex[2] = { pos.x - x, pos.y + y };
    vertex[3] = { pos.x - y, pos.y - x };
    //printf("%.1f : %.1f %.1f    %.1f %.1f    %.1f %.1f    %.1f %.1f\n", angle, vertex[0].x, vertex[0].y, vertex[1].x, vertex[1].y, vertex[2].x, vertex[2].y, vertex[3].x, vertex[3].y);

    this->move((sin(caterpillarDir / RADIAN) * move) * -1, (cos(caterpillarDir / RADIAN) * move));

    // calculate inscreen position
    if (obj.player.pos.x < WINDOW_WIDTH / 2) inScreenPos.x = obj.player.pos.x;
    else if (obj.player.pos.x > camera.imgWidth - WINDOW_WIDTH / 2) inScreenPos.x = obj.player.pos.x - (camera.imgWidth - WINDOW_WIDTH);
    else inScreenPos.x = WINDOW_WIDTH / 2;

    if (obj.player.pos.y < WINDOW_HEIGHT / 2) inScreenPos.y = obj.player.pos.y;
    else if (obj.player.pos.y > camera.imgHeight - WINDOW_HEIGHT / 2) inScreenPos.y = obj.player.pos.y - (camera.imgHeight - WINDOW_HEIGHT);
    else inScreenPos.y = WINDOW_HEIGHT / 2;

    // calculate player to mouse angle
    dir = atan2(mouse.pos.y - inScreenPos.y, mouse.pos.x - inScreenPos.x) * RADIAN;

    // calculate player's map position
    blockX = pos.x / 40;
    blockY = pos.y / 40;
}


//draw
void Player::draw() {
    int x = (int)(inScreenPos.x - (w / 2));
    int y = (int)(inScreenPos.y - (h / 2));
    SDL_Rect tmp;
    tmp.x = (caterpillarNum / 2) * 40, tmp.y = (caterpillarNum % 2) * 40, tmp.h = 40, tmp.w = 40;
    drawTextureAR(renderer, tmp, x, y, caterpillarDir, caterpillar);
    //drawTextureAR(renderer, tmp, x, y, 0, caterpillar);
    drawTexture(renderer, x, y, image);
    drawTextureR(renderer, x - 20, y - 20, dir, aim);
    if (led[0]) { // left
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, vertex[2].x - camera.pos.x, vertex[2].y - camera.pos.y, vertex[3].x - camera.pos.x, vertex[3].y - camera.pos.y);
    }
    if (led[1]) { // right
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, vertex[0].x - camera.pos.x, vertex[0].y - camera.pos.y, vertex[1].x - camera.pos.x, vertex[1].y - camera.pos.y);
    }
    if (led[2]) { // top
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, vertex[0].x - camera.pos.x, vertex[0].y - camera.pos.y, vertex[3].x - camera.pos.x, vertex[3].y - camera.pos.y);
    }
    if (led[3]) { // bottom
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, vertex[1].x - camera.pos.x, vertex[1].y - camera.pos.y, vertex[2].x - camera.pos.x, vertex[2].y - camera.pos.y);
    }
}


//###########################################################################
//#################################Bullet####################################






//SDL drawing function
void drawTexture(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture) {
    SDL_Rect src;
    SDL_Rect dst;

    src.x = 0;
    src.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

    dst.x = x;
    dst.y = y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void drawTextureA(SDL_Renderer* renderer, SDL_Rect src, int x, int y, SDL_Texture* texture) {
    SDL_Rect dst;

    dst.x = x;
    dst.y = y;
    dst.w = src.w;
    dst.h = src.h;
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void drawTextureR(SDL_Renderer* renderer, int x, int y, float angle, SDL_Texture* texture) {
    SDL_Rect src;
    SDL_Rect dst;
    SDL_Point center;

    src.x = 0;
    src.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

    dst.x = x;
    dst.y = y;
    dst.w = src.w;
    dst.h = src.h;
    center.x = dst.w / 2;
    center.y = src.h / 2;

    SDL_RenderCopyEx(renderer, texture, &src, &dst, angle, &center, SDL_FLIP_NONE);
}

void drawTextureAR(SDL_Renderer* renderer, SDL_Rect src, int x, int y, float angle, SDL_Texture* texture) {
    SDL_Rect dst;
    SDL_Point center;

    dst.x = x;
    dst.y = y;
    dst.w = src.w;
    dst.h = src.h;
    center.x = dst.w / 2;
    center.y = src.h / 2;
    SDL_RenderCopyEx(renderer, texture, &src, &dst, angle, &center, SDL_FLIP_NONE);
}

SDL_Texture* loadTexture(const char* file) {
    SDL_Surface* surface;
    SDL_Texture* texture;

    surface = IMG_Load(file);
    if (surface == NULL) {
        printf("fail to read %s\n", file);
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)  printf("unable to create texture.\n");
    SDL_FreeSurface(surface);

    return texture;
}

bool OutOfMap(Vector2 pos, int w, int h) {
    if (pos.x + (w / 2) < 0 || pos.y + (h / 2) < 0 || pos.x - (w / 2) > camera.imgWidth || pos.y - (h / 2) > camera.imgHeight) return true;
    return false;
}