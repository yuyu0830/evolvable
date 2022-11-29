#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

//handler
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;

//image
SDL_Texture* player = NULL;
SDL_Texture* wall = NULL;

float playerX = 300.f, playerY = 300.f;
float speed = 2.5f;
float wallPos[][2] = {{700.f, 400.f}};


//main::function
bool initAll();
bool closeAll();
void load();
void update();
void draw();
void inputCal(SDL_Event e);
void drawTexture(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture);
void drawTextureR(SDL_Renderer* renderer, int x, int y, float angle, SDL_Texture* texture);
void drawTextureA(SDL_Renderer* renderer, SDL_Rect src, int x, int y, SDL_Texture* texture);
void drawTextureAR(SDL_Renderer* renderer, SDL_Rect src, int x, int y, float angle, SDL_Texture* texture);
SDL_Texture* loadTexture(const char* file);
void drawCircle(SDL_Point pos, float r);


//global var
bool keys[255] = { 0, };

int main(int argv, char** args) {
    srand(time(NULL));
    bool running = initAll();
    if (running) {
        load();
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

void inputCal(SDL_Event event) {
    switch (event.type) {
    case SDL_KEYDOWN:
        printf("%d\n", event.key.keysym.scancode);
        keys[event.key.keysym.scancode] = true;
        break;
    case SDL_KEYUP:
        keys[event.key.keysym.scancode] = false;
        break;
    /*case SDL_MOUSEMOTION:
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
        break;*/
    }
}

bool initAll() {
    //initialize video
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Video Initialize failed! error code : %s\n", (SDL_GetError()));
        return 0;
    }

    //initialize window
    window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL);
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
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 1;
}

void load() {
    player = loadTexture("src/Player.png");
    wall = loadTexture("src/tile_blue.png");
}

void update() {
    int moveX = 0, moveY = 0;
    if (keys[26]) {
        playerY -= speed;
    }

    if (keys[22]) {
        playerY += speed;
    }

    if (keys[4]) {
        playerX -= speed;
    }

    if (keys[7]) {
        playerX += speed;
    }

    float len = sqrt(pow(playerX - wallPos[0][0], 2) + pow(playerY - wallPos[0][1], 2));
    SDL_FPoint v = { ((playerX - wallPos[0][0]) / len), ((playerY - wallPos[0][1]) / len) };

    printf("%.2f", len);
    if (len <= 46) {
        playerX += v.x * (46 - len);
        playerY += v.y * (46 - len);
    }
    printf("\n");
    
}

//draw
void draw() {
    SDL_RenderClear(renderer);
    drawTexture(renderer, wallPos[0][0] - 30, wallPos[0][1] - 26, wall);
    drawTexture(renderer, playerX - 20, playerY - 20, player);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderDrawPoint(renderer, playerX, playerY);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderPresent(renderer);
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

void drawCircle(SDL_Point pos, float r) {
    int old_x = 0;
    int old_y = 0;
    int x1, x2, y1, y2;
    for (int i = 1; i <= 180; i++) {
        x1 = old_x;
        y1 = old_y;
        x2 = sin(57.295791f * i) * r;
        y2 = cos(57.295791f * i) * r;
        SDL_RenderDrawLine(renderer, x1 + pos.x, y1 + pos.y, x2 + pos.x, y2 + pos.y);

        old_x = x2;
        old_y = y2;
    }
}