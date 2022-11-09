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
    Vector2(float _x, float _y) : x(_x), y(_y) { };
};

struct Mouse {
    SDL_Point pos;
    bool click[2];
    bool clicked[2] = { 0, };
};

Vector2 VecAdd(Vector2 a, Vector2 b, float speed = 1) { return Vector2(a.x + (b.x * speed), a.y + (b.y * speed)); }
float Sign(float x) { if (x < 0) return -1; return 1; }
//bool OutOfMap(Vector2 pos, int w, int h) {
//    if (pos.x + (w / 2) < 0 || pos.y + (h / 2) < 0 || pos.x - (w / 2) > WINDOW_WIDTH || pos.y - (h / 2) > WINDOW_HEIGHT) return true;
//    return false;
//}

