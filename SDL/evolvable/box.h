#pragma once
#define WINDOW_TITLE "HELLO"
#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600
#define _CRT_SECURE_NO_WARNINGS
#define RADIAN 57.295791f
#define BULLETSIZE 100WINDOW_WIDTH
#define DIAGONAL_LENGTH 28.284271f

class App {
public:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	TTF_Font* font = NULL;

	~App() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_CloseFont(font);
	}
};