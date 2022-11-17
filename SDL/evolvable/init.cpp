#include "init.h"
#include "game.h"

bool init(App *app) {
    //initialize video
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Video Initialize failed! error code : %s\n", (SDL_GetError()));
        return 0;
    }

    //initialize window
    app -> window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (app -> window == 0) {
        printf("Create window failed! error code : %s\n", (SDL_GetError()));
        return 0;
    }

    //initialize renderer
    app -> renderer = SDL_CreateRenderer(app -> window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (app -> renderer == 0)
    {
        printf("Renderer Initialize failed! error code : %s\n", (SDL_GetError()));
        return 0;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        printf("Image initialize failed! error code : %s\n", (IMG_GetError()));
        return 0;
    }

    if (TTF_Init() != 0) {
        printf("Font initialize failed! error code : %s\n", TTF_GetError());
        return 0;
    }

    app -> font = TTF_OpenFont("src/font/HBIOS-SYS.ttf", 32);
    if (app -> font == NULL) {
        printf("Failed to load font!\n");
        return 0;
    }

    return 1;
}