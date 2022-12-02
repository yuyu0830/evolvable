#include "box.h"

//###########################################################
//###########################################################
App::~App() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	font = NULL;
    for (int i = 0; i < 3; i++) {
        SDL_FreeCursor(cursor[i]);
    }
	printf("App destroy complete!");
}


//###########################################################
//###########################################################
LTimer::LTimer()
{
    //Initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void LTimer::start()
{
    //Start the timer
    mStarted = true;

    //Unpause the timer
    mPaused = false;

    //Get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void LTimer::stop()
{
    //Stop the timer
    mStarted = false;

    //Unpause the timer
    mPaused = false;

    //Clear tick variables
    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause()
{
    //If the timer is running and isn't already paused
    if (mStarted && !mPaused)
    {
        //Pause the timer
        mPaused = true;

        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

void LTimer::unpause()
{
    //If the timer is running and paused
    if (mStarted && mPaused)
    {
        //Unpause the timer
        mPaused = false;

        //Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        //Reset the paused ticks
        mPausedTicks = 0;
    }
}

Uint32 LTimer::getTicks()
{
    //The actual timer time
    Uint32 time = 0;

    //If the timer is running
    if (mStarted)
    {
        //If the timer is paused
        if (mPaused)
        {
            //Return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}


bool LTimer::isStarted()
{
    //Timer is running and paused or unpaused
    return mStarted;
}

bool LTimer::isPaused()
{
    //Timer is running and paused
    return mPaused && mStarted;
}


//###########################################################
//###########################################################
float pow(float v) {
    return v * v;
}

void fpointAdd(SDL_FPoint* a, SDL_FPoint b) {
    a->x += b.x;
    a->y += b.y;
}

bool isin(int target, int start, int end) {
    if (target < start) return 0;
    if (target > end) return 0;
    return 1;
}

bool isin(float target, float start, float end) {
    if (target < start) return 0;
    if (target > end) return 0;
    return 1;
}

SDL_Point posToTile(SDL_FPoint pos) {
    int x = (int)((pos.x + 15) / 45), tmp = 0;
    if (x % 2 == 0) tmp = 1;
    return { x, (int) ((pos.y + (tmp * 26)) / 52) };
}

SDL_FPoint tileToPos(SDL_Point tile) {
    int x = tile.x * 45 - 15, tmp = 0;
    if (tile.x % 2 == 0) tmp = 1;
    int y = tile.y * 52 - (tmp * 26);
    return { (float)x + 15, (float)y + 26};
}

SDL_FPoint collision(SDL_FPoint a, SDL_FPoint b) {
    float len = sqrt(pow(a.x - b.x) + pow(a.y - b.y));
    if (len < 46) {
        return { ((a.x - b.x) / len) * (46 - len), ((a.y - b.y) / len) * (46 - len) };
    }
    return { 0, 0 };
}
