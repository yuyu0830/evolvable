#pragma once
#define WINDOW_TITLE "WTF"
#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 720
#define RADIAN 57.295791f
#define BULLETSIZE 100

typedef struct Vector2 {
    float x, y;
    Vector2() {
        x = 0.0f;
        y = 0.0f;
    }
    Vector2(int _x, int _y) : x(_x), y(_y) { };
};

struct Mouse {
    SDL_Point pos;
    bool click[2];
    bool clicked[2] = { 0, };
};