#ifndef BOX_H
#define BOX_H

#include <ostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

const char WINDOW_TITLE[] = "WTF";
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
const int TILE_X = 60;
const int TILE_Y = 52;

const int BULLETSIZE = 100;
const float RADIAN = 57.295791f;
const float DIAGONAL_LENGTH = 28.284271f;

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

class App {
public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Cursor* cursor[3]; //green, yellow, red
	~App();
};

struct Input {
	Uint32 keys[255];
	Uint32 mouseClick[3];
	bool mouseClicked[3];
	SDL_Point mousePos;
};

struct Timer {
	LTimer program;
	LTimer frame;
	LTimer game;
};

#endif