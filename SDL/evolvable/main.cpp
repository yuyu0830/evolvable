#include <stdio.h>
#include <stdbool.h>

#include "game.h"
#include "init.h"

// Define screen dimensions

using namespace std;

App app;

int main(int argv, char** args) {
    if (init(&app)) {
        game(&app);
    }
    else {
        printf("Game running Failed!\nPlease try again!\n");
    }
    return 0;
}