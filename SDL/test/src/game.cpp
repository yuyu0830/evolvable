#include "game.h"

Game::Game() {
    //Start timer
    timer.program.start();
    frameCounter = 0;
    fps = 0.f;

    //Initialize Game and Start Game!
    if (this->init()) {
        this->gameLoop();
    }
    else {
        printf("Please try again...\n");
    }
}

Game::~Game() {
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
}

bool Game::init() {
    srand(time(NULL));
    //initialize video
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        printf("Video Initialize Success!\n");
    }
    else {
        printf("Video Initialize failed! error code : %s\n", (SDL_GetError()));
        return 0;
    }

    //initialize window
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (window != NULL) {
        printf("Create Window Success!\n");
    }
    else {
        printf("Create window failed! error code : %s\n", (SDL_GetError()));
        return 0;
    }

    if (object.init(window)) {
        printf("Renderer Initialize Success!\n");
    }
    else {
        printf("Renderer Initialize failed! error code : %s\n", (SDL_GetError()));
    }
    ////initialize renderer
    //renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //if (renderer != NULL)
    //{
    //    printf("Renderer Initialize Success!\n");
    //}
    //else {
    //    printf("Renderer Initialize failed! error code : %s\n", (SDL_GetError()));
    //    return 0;
    //}

    //initialize IMG
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == IMG_INIT_PNG) {
        printf("Image library Initialize Success!\n");
    }
    else {
        printf("Image library Initialize failed! error code : %s\n", (IMG_GetError()));
        return 0;
    }

    //initialize TTF
    if (TTF_Init() == 0) {
        printf("Font Initialize Success!\n");
    }
    else {
        printf("Font initialize failed! error code : %s\n", TTF_GetError());
        return 0;
    }

    //initialize font
    font = TTF_OpenFont("src/font/HBIOS-SYS.ttf", 32);
    if (font != NULL) {
        printf("Load Font Success!\n");
    }
    else {
        printf("Failed to load font!\n");
        return 0;
    }

    printf("Game initialize Complete!\n");

    running = true;
    object.tmp();
    return 1;
}

void Game::gameLoop() {
    while (running) {
        timer.frame.start();

        running = object.update();
        object.draw();

        fpsHandling();
    }
}

void Game::fpsHandling() {
    fps = frameCounter / (timer.program.getTicks() / 1000.0f);
    int frameTicks = timer.frame.getTicks();
    if (frameTicks < SCREEN_TICK_PER_FRAME) {
        SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
    }
    frameCounter++;
}