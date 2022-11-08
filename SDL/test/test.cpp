#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
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
bool initAll();
bool closeAll();
void update();
void draw();
void inputCal(SDL_Event e);
void drawTexture(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture);
void drawTextureEx(SDL_Renderer* renderer, int x, int y, float angle, SDL_Texture* texture);
void drawBackground(SDL_Renderer* renderer, int startx, int starty, SDL_Texture* texture);
SDL_Texture* loadTexture(const char* file);

//global var
bool keys[255] = { 0, };
Mouse mouse;
OBJManager obj;
//Camera camera;
SDL_Texture* bullet1 = NULL;
SDL_Texture* backgroundIMG = NULL;
vector<int> activeBulletNum;

int main(int argv, char** args) {
    bool running = initAll();
    obj.player.init(Vector2(500, 300), 3.0f, loadTexture("src/Player.png"));
    bullet1 = loadTexture("src/bullet.png");
    backgroundIMG = loadTexture("src/background.png");
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

//update functions
//main update function
void update() {
    int playerX = 0, playerY = 0;
    if (keys[(int)'w']) {
        playerY -= 1;
    }
    if (keys[(int)'s']) {
        playerY += 1;
    }
    if (keys[(int)'a']) {
        playerX -= 1;
    }
    if (keys[(int)'d']) {
        playerX += 1;
    }
    obj.player.move(Vector2(obj.player.speed * x, obj.player.speed * y));
    if (mouse.click[0] && !mouse.clicked[0]) {
        mouse.clicked[0] = true;
        obj.BulletCreate();
    }
    obj.BulletCalc();
    obj.player.dirUpdate();
    //obj.BulletCalc();
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
        if (event.button.button == SDL_BUTTON_LEFT) mouse.click[0] = true;
        else if (event.button.button == SDL_BUTTON_RIGHT) mouse.click[1] = true;
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

//Object update function
void Object::init(Vector2 _pos, float _speed, SDL_Texture* _image) {
    pos = _pos;
    speed = _speed;
    image = _image;
    SDL_QueryTexture(_image, NULL, NULL, &w, &h);
}

void Object::move(Vector2 _des) {
    pos = VecAdd(pos, _des, speed);
}

//OBJManager update function
void OBJManager::BulletCreate() {
    if (bulletNum < BULLETSIZE) {
        int tmpNum = 0;
        while (bullet[tmpNum].active) {
            tmpNum++;
        }
        bullet[tmpNum].active = true;
        bullet[tmpNum].init(player.pos, 2.5, bullet1);

        float x, y, len;
        x = mouse.pos.x - bullet[tmpNum].pos.x;
        y = mouse.pos.y - bullet[tmpNum].pos.y;
        len = sqrt(x * x + y * y);
        x /= len;
        y /= len;
        bullet[tmpNum].dir = Vector2(x * x * Sign(x), y * y * Sign(y));
        bulletNum++;
    }
}

void OBJManager::BulletCalc() {
    int sum = 0;
    for (int i = 0; i < BULLETSIZE; i++) {
        if (bullet[i].active) {
            bullet[i].move(bullet[i].dir);
            if (OutOfDisplay(bullet[i].pos, bullet[i].w, bullet[i].h)) {
                bullet[i].active = false;
                //printf("Bullet %d disabled!\n", i);
            }
            sum++;
            activeBulletNum.push_back(i);
            if (sum >= bulletNum) return;
        }
    }
}

//Player update function
void Player::dirUpdate() {
    float dx = mouse.pos.x - pos.x;
    float dy = mouse.pos.y - pos.y;
    dir = atan2(dy, dx) * RADIAN;
}

////Bullet update function


//drawing function
//main draw function
void draw() {
    SDL_RenderClear(renderer);
    //obj.player.objDraw(obj.player.dir);
    //obj.BulletDraw();
    SDL_RenderPresent(renderer);
}

//object update function
void Object::objDraw(float _dir) {
    if (_dir == 0) {
        drawTexture(renderer, (int)pos.x - (w / 2), (int)pos.y - (h / 2), image);
    }
    else drawTextureEx(renderer, (int)pos.x - (w / 2), (int)pos.y - (h / 2), _dir, image);
}

//OBJManager draw function
void OBJManager::BulletDraw() {
    for (int i : activeBulletNum) {
        bullet[i].objDraw();
    }
    activeBulletNum.clear();
}
//Player draw function

////Bullet draw function

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

void drawBackground(SDL_Renderer* renderer, int startx, int starty, SDL_Texture* texture) {
    SDL_Rect src;
    SDL_Rect dst;

    src.x = startx;
    src.y = starty;
    src.w = WINDOW_WIDTH;
    src.h = WINDOW_HEIGHT;

    dst.x = 0;
    dst.y = 0;
    dst.w = WINDOW_WIDTH;
    dst.h = WINDOW_HEIGHT;

    SDL_RenderCopy(renderer, texture, &src, &dst);
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