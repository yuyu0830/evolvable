#include <SDL.h>
#include <SDL_image.h>
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

using namespace std;

//handler
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

//main::function
bool OutOfMap(Vector2 pos, int w, int h);
bool initAll();
bool closeAll();
void update();
void draw();
void inputCal(SDL_Event e);
void drawTexture(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture);
void drawTextureEx(SDL_Renderer* renderer, int x, int y, float angle, SDL_Texture* texture);
void drawTextureCut(SDL_Renderer* renderer, SDL_Rect src, int x, int y, float angle, SDL_Texture* texture);
SDL_Texture* loadTexture(const char* file);

//global var
bool keys[255] = { 0, };
Mouse mouse;
OBJManager obj;
SDL_Texture* bullet1 = NULL;
SDL_Texture* walls = NULL;
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
    obj.player.move();
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
        keys[event.key.keysym.sym] = true;
        break;
    case SDL_KEYUP:
        keys[event.key.keysym.sym] = false;
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
    // initialize video
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Video Initialize failed! error code : %s\n", (SDL_GetError()));
        return 0;
    }

    // initialize window
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (window == 0) {
        printf("Create window failed! error code : %s\n", (SDL_GetError()));
        return 0;
    }

    // initialize renderer
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

    return 1;
}

bool closeAll() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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

//draw
void Camera::drawBackground() {
    SDL_Rect src;
    SDL_Rect dst;

    src.x = pos.x;
    src.y = pos.y;
    src.w = WINDOW_WIDTH;
    src.h = WINDOW_HEIGHT;

    dst.x = 0;
    dst.y = 0;
    dst.w = WINDOW_WIDTH;
    dst.h = WINDOW_HEIGHT;

    SDL_RenderCopy(renderer, backgroundIMG, &src, &dst);
}

void Camera::drawWalls() {
    SDL_Rect src;
    SDL_Rect dst;
    int cnt = 0;
    short startX = pos.x / 40, endX = (pos.x + WINDOW_WIDTH + 39) / 40;
    short startY = pos.y / 40, endY = (pos.y + WINDOW_WIDTH + 39) / 40;
    for (int i = startX; i < endX; i++) {
        for (int j = startY; j < endY; j++) {
            if (map[i][j] != 0) {
                src.x = ((map[i][j] - 1) % 5) * 40;
                src.y = ((map[i][j] - 1) / 5) * 40;
                src.w = 40;
                src.h = 40;

                dst.x = i * 40 - pos.x;
                dst.y = j * 40 - pos.y;
                dst.w = 40;
                dst.h = 40;

                SDL_RenderCopy(renderer, wall, &src, &dst);
            }
            cnt++;
        }
    }
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
        else drawTextureEx(renderer, (int)pos.x - (w / 2), (int)pos.y - (h / 2), _dir, image);
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
    caterpillarDir = 90.0f;
    inScreenPos = Vector2(0, 0);
    blockX = 0;
    blockY = 0;
    SDL_QueryTexture(_image, NULL, NULL, &w, &h);
}

void Player::update() {
    if (obj.player.pos.x < WINDOW_WIDTH / 2) inScreenPos.x = obj.player.pos.x;
    else if (obj.player.pos.x > camera.imgWidth - WINDOW_WIDTH / 2) inScreenPos.x = obj.player.pos.x - (camera.imgWidth - WINDOW_WIDTH);
    else inScreenPos.x = WINDOW_WIDTH / 2;

    if (obj.player.pos.y < WINDOW_HEIGHT / 2) inScreenPos.y = obj.player.pos.y;
    else if (obj.player.pos.y > camera.imgHeight - WINDOW_HEIGHT / 2) inScreenPos.y = obj.player.pos.y - (camera.imgHeight - WINDOW_HEIGHT);
    else inScreenPos.y = WINDOW_HEIGHT / 2;

    dir = atan2(mouse.pos.y - inScreenPos.y, mouse.pos.x - inScreenPos.x) * RADIAN;
    blockX = pos.x / 40;
    blockY = pos.y / 40;
}

void Player::move() {
    int move = 0;
    if (keys[(int)'w']) {
        if (pos.y > h / 2) {
            move -= 1;
        }
        else pos.y = h / 2;
    }
    if (keys[(int)'s']) {
        if (pos.y < camera.imgHeight - h / 2) {
            move += 1;
        }
        else pos.y = camera.imgHeight - h / 2;
    }
    if (keys[(int)'a']) {
        caterpillarDir -= 1.4f;
    }
    if (keys[(int)'d']) {
        caterpillarDir += 1.4f;
    }


    if (caterpillarDir > 360) caterpillarDir -= 360;
    else if (caterpillarDir < 0) caterpillarDir += 360;


    pos = VecAdd(pos, Vector2(cos(caterpillarDir / RADIAN), sin(caterpillarDir / RADIAN)), move);
    //printf("    %d       %d %d     %.1f %.1f\n  %d  %d\n    %d\n", (int)((pos.y - (h / 2)) / 40), blockX, blockY, pos.x, pos.y, (int)((pos.x - (w / 2)) / 40), (int)((pos.x + (w / 2)) / 40), (int)((pos.y + (h / 2)) / 40));
    int top = (int) ((pos.y + 1 - h / 2) / 40);
    int bot = (int) ((pos.y - 1 + h / 2) / 40);
    int left = (int) ((pos.x + 1 - w / 2) / 40);
    int right = (int) ((pos.x - 1 + w / 2) / 40);
    printf("%f\n", caterpillarDir);
    if (move) {
        caterpillarNum = (caterpillarNum + 1) % 3;
        if (caterpillarDir < 180) {
            if (camera.map[left][top] || camera.map[right][top]) pos.y = blockY * h + h / 2;
        }
        else if (caterpillarDir > 180) {
            if (camera.map[left][bot] || camera.map[right][bot]) pos.y = blockY * h + h / 2;
        }
        if (caterpillarDir > 270 || caterpillarDir < 90) {
            if (camera.map[left][top] || camera.map[left][bot]) pos.x = blockX * w + w / 2;
        }
        else {
            if (camera.map[right][top] || camera.map[right][bot]) pos.x = blockX * w + w / 2;
        }
    }
    
}
//draw
void Player::draw() {
    int x = (int)(inScreenPos.x - (w / 2));
    int y = (int)(inScreenPos.y - (h / 2));
    SDL_Rect tmp;
    tmp.x = (caterpillarNum / 2) * 40, tmp.y = (caterpillarNum % 2) * 40, tmp.h = 40, tmp.w = 40;
    drawTextureCut(renderer, tmp, x, y, caterpillarDir, caterpillar);
    drawTexture(renderer, x, y, image);
    drawTextureEx(renderer, x - 20, y - 20, dir, aim);
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

void drawTextureEx(SDL_Renderer* renderer, int x, int y, float angle, SDL_Texture* texture) {
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


void drawTextureCut(SDL_Renderer* renderer, SDL_Rect src, int x, int y, float angle, SDL_Texture* texture) {
    SDL_Rect dst;
    SDL_Point center;

    dst.x = x;
    dst.y = y;
    dst.w = src.w;
    dst.h = src.h;
    center.x = dst.w / 2;
    center.y = src.h / 2;
    SDL_RenderCopyEx(renderer, texture, &src, &dst, (int) (angle + 270) % 360, &center, SDL_FLIP_NONE);
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