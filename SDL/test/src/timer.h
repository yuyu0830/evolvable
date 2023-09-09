#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

#include "util.h"

class Timer {
public:
	Timer();
	static void start(timer timerType);
	static void stop(timer timerType);
	static void pause(timer timerType);
	static void unpause(timer timerType);

	static void frameSynchronization();

	static Uint32 getTicks(timer timerType);
	static float getFps();
	
	static bool isStarted(timer timerType);
	static bool isPaused(timer timerType);

private:
	static Uint32 startTicks[TIMER_AMOUNT];
	static Uint32 pausedTicks[TIMER_AMOUNT];

	static bool paused[TIMER_AMOUNT];
	static bool started[TIMER_AMOUNT];
	static int frameCounter;
	static float fps;
};

#endif