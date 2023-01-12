#include "renderer.h"

Renderer::Renderer() {
	renderer = NULL;
	window = NULL;
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(renderer);
}

Renderer* Renderer::getInstance() {
	return Singleton<Renderer>::get();
}


bool Renderer::set() {
	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if (window) {
		printf("Create Window Success!\n");
	}
	else {
		printf("Create window failed! error code : %s\n", (SDL_GetError()));
		return 0;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer) {
		printf("Renderer Initialize Success!\n");
		return 1;
	}
	else {
		printf("Renderer Initialize failed! error code : %s\n", (SDL_GetError()));
		return 0;
	}
}

SDL_Renderer* Renderer::getRenderer() {
	return renderer;
}