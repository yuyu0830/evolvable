#include "game.h"

void game(App *app) {
    SDL_Event event;
    bool running = true;
    Uint32 lastest = 0;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        printf("%u\n", SDL_GetTicks() - lastest);
        lastest = SDL_GetTicks();
    }
}