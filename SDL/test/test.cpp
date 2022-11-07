#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include "box.h"
#include "player.h"
#include "object.h"
#include "bullet.h"
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
SDL_Texture* loadTexture(const char* file);

//global var
bool keys[255] = { 0, };
Mouse mouse;
OBJManager obj;
SDL_Texture* bullet1 = NULL;

int main(int argv, char** args) {
    bool running = initAll();
    obj.player.init(500, 300, loadTexture("src/Player.png"));
    obj.bullet.image = loadTexture("src/bullet.png");
    if (running) {
        SDL_Event event;
        while (running) {
            // calculate input
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) running = false;
                else inputCal(event);
            }
            update();
            draw();
            //printf("%d, %d\n", (int) obj.player.x, (int) obj.player.y);
            /*printf("[");
            for (int i = 0; i < 255; i++)  if (keys[i]) printf("%c ", (char)i);
            printf("]\n");*/
            //printf("[%f %f]\n", obj.bullet[0].x, obj.bullet[0].y);
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
    if (keys[(int)'w']) obj.player.y--;
    if (keys[(int)'s']) obj.player.y++;
    if (keys[(int)'a']) obj.player.x--;
    if (keys[(int)'d']) obj.player.x++;
    if (mouse.click[0] && !mouse.clicked[0]) {
        printf("!");
        mouse.clicked[0] = true;
        obj.bullet.Create(obj.player.x, obj.player.y, 1);
    }
    //obj.bulletCalculation();
    obj.player.dirUpdate();
    obj.bullet.Calc();
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
void Object::move(float _x, float _y) {
    x += _x;
    y += _y;
}

//OBJManager update function

//Player update function
void Player::init(int _x, int _y, SDL_Texture* _texture) {
    x = _x;
    y = _y;
    image = _texture;
    dir = 0.0f;
}

void Player::dirUpdate() {
    float dx = mouse.pos.x - x;
    float dy = mouse.pos.y - y;
    dir = atan2(dy, dx) * RADIAN;
}

//Bullet update function
void Bullet::Create(int _x, int _y, int _speed) {
    if (obj.bullet.bulletNum < BULLETSIZE) {
        obj.bullet.bulletNum++;
        int tmpNum = 0;
        float x, y, len;
        while (obj.bullet.active[tmpNum]) { tmpNum++; }
        obj.bullet.active[tmpNum] = true;
        obj.bullet.speed[tmpNum] = 1;
        obj.bullet.pos[tmpNum] = Vector2(obj.player.x, obj.player.y);
        x = mouse.pos.x - _x;
        y = mouse.pos.y - _y;
        len = sqrt(x * x + y * y);
        x /= len;
        y /= len;
        obj.bullet.dir[tmpNum] = Vector2(x * x * Sign(x), y * y * Sign(y));
    }
}

void Bullet::Reset(int _bulletNum) {
    obj.bullet.active[_bulletNum] = false;
    obj.bullet.bulletNum--;
}

void Bullet::Calc() {
    for (int i = 0; i <= BULLETSIZE; i++) {
        if (obj.bullet.active[i]) {
            if (OutOfDisplay(obj.bullet.pos[i])) {
                obj.bullet.Reset(i);
                printf("!\n");
            }
            else obj.bullet.pos[i] = VecAdd(obj.bullet.pos[i], obj.bullet.dir[i]);
        }
    }
}


//drawing function
//main draw function
void draw() {
    SDL_RenderClear(renderer);
    obj.player.objDraw(obj.player.dir);
    obj.bullet.bulletDraw();
    SDL_RenderPresent(renderer);
}

//object update function
void Object::objDraw(float _dir) {
    if (_dir == 0) {
        drawTexture(renderer, (int)x, (int)y, image);
    }
    else drawTextureEx(renderer, (int)x, (int)y, _dir, image);
}

//OBJManager draw function

//Player draw function

//Bullet draw function
void Bullet::bulletDraw() {
    int sum = 0;
    for (int i = 0; i <= BULLETSIZE; i++) {
        if (obj.bullet.active[i]) {
            sum++;
            //printf("%f, %f\n", obj.bullet.dir[i].x, obj.bullet.dir[i].y);
            drawTexture(renderer, obj.bullet.pos[i].x, obj.bullet.pos[i].y, obj.bullet.image);
        }
        if (sum == obj.bullet.bulletNum) return;
    }
}

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