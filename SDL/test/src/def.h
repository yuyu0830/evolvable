#ifndef DEF_H
#define DEF_H

#include <SDL.h>

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

struct Input {
	bool keys[255];
	bool mouseClick[3];
	bool mouseClicked[3];
	SDL_Point mousePos;
};

class LTimer
{
public:
	//Initializes variables
	LTimer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	Uint32 getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

private:
	//The clock time when the timer started
	Uint32 mStartTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;

	//The timer status
	bool mPaused;
	bool mStarted;
};

struct Timer {
	LTimer program;
	LTimer frame;
	LTimer game;
};

typedef enum {
	TAG_PLAYER = 1,
	TAG_ENEMY = 2,
	TAG_NEUTRAL = 3,
	TAG_OBJECT = 4,
	TAG_WALL = 5,
	TAG_UI = 6
} tag;

#endif