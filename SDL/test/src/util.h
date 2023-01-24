#ifndef UTIL_H
#define UTIL_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <SDL_mouse.h>

const char WINDOW_TITLE[] = "test game";
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

const int MAX_FRAME_NUMBER = 5;      // 한 Graphic 개체가 가질 수 있는 Texture 개수
const int MAX_GRAPHIC_NUMBER = 5;    // 한 Object 개체가 가질 수 있는 Graphic 개수 

const float RADIAN = 57.295791f;

const SDL_Color COLOR_BLACK = { 0x00, 0x00, 0x00 };
const SDL_Color COLOR_WHITE = { 0xFF, 0xFF, 0xFF };
const SDL_Color COLOR_RED = { 0xFC, 0x00, 0x00 };
const SDL_Color COLOR_BLUE = { 0x12 ,0x01, 0xFC };
const SDL_Color COLOR_GREEN = { 0x03, 0xB7, 0x2A };
const SDL_Color COLOR_YELLOW = { 0xFC, 0xE3, 0x03 };
const SDL_Color COLOR_VIOLET = { 0xB8, 0x01, 0xF9 };
const SDL_Color COLOR_PINK = { 0xF4, 0x73, 0x25 };

struct Size {
	int width;
	int height;
};

struct ObjectData {
	char name[20];
	int tag;
	int unitNum;
};

struct UnitData {
	bool invincible;
	float atk;
	float maxHP;
	float curHP;
	float speed;
};

struct TextContainer {
	SDL_Color color;
	TTF_Font* font;

	char text[20];
};

typedef enum {
	TAG_PLAYER,
	TAG_ENEMY,
	TAG_NEUTRAL,
	TAG_OBJECT,
	TAG_WALL,
	TAG_BULLET,
	TAG_UI,
	TAG_BACKGROUND,
	TAG_NUMBER
} tag;

typedef enum {
	PLAYER_DEFAULT,
	ENEMY_DEFAULT,
	UI_BUTTON,
	UI_TILE,
	UI_BACKGROUND,
	TYPENUM
} type;

typedef enum {
	BUTTON,
	BUTTON_MOUSE_ON,
	BUTTON_MOUSE_OFF,
	TILE,
	TILE_1,
	TILE_2,
	TILE_3,
	TILE_4,
	TILE_5,
	PARTSNUM = 20
} parts;

typedef enum {
	SHAPE_CIRCLE,
	SHAPE_SQUARE,
	SHAPE_HEXAGON,
	SHAPE_POINT,
	SHAPE_SQUAREEX,
	SHAPE_NUMBER
} shape;

typedef enum {
	TIMER_PROGRAM,
	TIMER_FRAME,
	TIMER_INGAME,
	TIMER_NUMBER
} timer;

typedef enum {
	MENU_MAIN_SCENE,
	MENU_SETTING_SCENE,
	MENU_MAP_SELECT_SCENE
} menuScene;
#endif