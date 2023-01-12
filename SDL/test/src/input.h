#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

#include "timer.h"

class Input {
public:
	Input();
	static bool eventHandling();
	static Uint32 getKeys(SDL_Scancode key);
	static Uint32 getMouseClick(Uint8 button);
	static Uint32 getMouseClicked(Uint8 button);
	static void setMouseClicked(Uint8 button);
	static SDL_Point getMousePosition();

private:
	static Uint32 keys[255];
	static Uint32 mouseClick[6];
	static Uint32 mouseClicked[6];
	static SDL_Point mousePosition;
};

#endif