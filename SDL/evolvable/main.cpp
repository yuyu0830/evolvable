#include <stdio.h>
#include <stdbool.h>
#include <string>
#include <vector>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "game.h"
#include "init.h"
#include "box.h"

// Define screen dimensions

using namespace std;

App app;
int main(int argv, char** args) {
    bool running = init();
    if (running) {
        game();
    }
    else {
        printf("Game running Failed!\nPlease try again!\n");
    }
    return 0;
}