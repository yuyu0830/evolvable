#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>

#include "game.h"

// Define screen dimensions
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main(int argv, char** args) {
    srand(time(NULL));
    
}