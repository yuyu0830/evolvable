#include "timer.h"

Uint32 Timer::startTicks[TIMER_AMOUNT];
Uint32 Timer::pausedTicks[TIMER_AMOUNT];

bool Timer::paused[TIMER_AMOUNT];
bool Timer::started[TIMER_AMOUNT];

int Timer::frameCounter = 0;
float Timer::fps = 0.f;

Timer::Timer() {
    for (int i = 0; i < 3; i++) {
        startTicks[i] = 0;
        pausedTicks[i] = 0;

        paused[i] = false;
        started[i] = false;
    }
}
    
void Timer::start(timer timerType) {
    started[timerType] = true;
    paused[timerType] = false;

    startTicks[timerType] = SDL_GetTicks();
    pausedTicks[timerType] = 0;
}

void Timer::stop(timer timerType) {
    started[timerType] = false;
    paused[timerType] = false;

    startTicks[timerType] = 0;
    pausedTicks[timerType] = 0;
}

void Timer::pause(timer timerType) {
    if (started[timerType] && !paused[timerType])
    {
        paused[timerType] = true;
        pausedTicks[timerType] = SDL_GetTicks() - startTicks[timerType];
        startTicks[timerType] = 0;
    }
}

void Timer::unpause(timer timerType) {
    if (started[timerType] && paused[timerType])
    {
        paused[timerType] = false;
        startTicks[timerType] = SDL_GetTicks() - pausedTicks[timerType];
        pausedTicks[timerType] = 0;
    }
}

void Timer::frameSynchronization() {
    fps = frameCounter / (getTicks(TIMER_PROGRAM) / 1000.0f);
    int frameTicks = getTicks(TIMER_FRAME);
    if (frameTicks < SCREEN_TICK_PER_FRAME) {
        SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
    }
    frameCounter++;
}

Uint32 Timer::getTicks(timer timerType) {
    Uint32 time = 0;
    if (started[timerType])
    {
        if (paused[timerType])
        {
            time = pausedTicks[timerType];
        }
        else
        {
            time = SDL_GetTicks() - startTicks[timerType];
        }
    }
    return time;
}

float Timer::getFps() {
    return fps;
}

bool Timer::isStarted(timer timerType) {
    return started[timerType];
}

bool Timer::isPaused(timer timerType) {
    return paused[timerType] && started[timerType];
}