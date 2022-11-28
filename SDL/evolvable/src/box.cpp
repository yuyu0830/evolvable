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

SDL_Point tileToPos(SDL_Point tile) {
    int tmp;
    if (tile.x % 2 == 0) tmp = 0;
    else tmp = 26;
    return { tile.x * 45, tile.y * 52 + tmp };
}

SDL_Point tileToPos(SDL_FPoint tile) {
    int tmp;
    if ((int)tile.x % 2 == 0) tmp = 0;
    else tmp = 26;
    return { (int)(tile.x * 45), (int)(tile.y * 52 + tmp) };
}

SDL_Point posToTile(SDL_Point pos) {
    int tmp;
    if (pos.x % 2 == 0) tmp = 0;
    else tmp = 26;
    return {(pos.x + 30) / 45, (pos.y + tmp) / 52};
}

SDL_Point posToTile(SDL_FPoint pos) {
    int tmp;
    if ((int)pos.x % 2 == 0) tmp = 0;
    else tmp = 26;
    return { (int)((pos.x + 30) / 45), (int)((pos.y + tmp) / 52) };
}