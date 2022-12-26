#ifndef DEF_H
#define DEF_H

const char WINDOW_TITLE[] = "test game";
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

struct objectData {
	char name[20];
	int tag;
	int unitNum;
};

typedef enum {
	TAG_PLAYER = 1,
	TAG_ENEMY = 2,
	TAG_NEUTRAL = 3,
	TAG_OBJECT = 4,
	TAG_WALL = 5,
	TAG_UI = 6
};

#endif