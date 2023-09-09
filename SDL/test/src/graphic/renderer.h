#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>

#include <SDL.h>

#include "../util.h"
#include "../singleton.h"

class Renderer {
public:
	static Renderer* getInstance();

	bool set();
	SDL_Renderer* getRenderer();

private:
	Renderer();
	~Renderer();
	SDL_Window* window;
	SDL_Renderer* renderer;

protected:
	friend class Singleton<Renderer>;
};

#endif