#include "game.h"

Game::Game() {
    if (this->init()) {
        this->gameLoop();
    }
    else {
        printf("Please try again\n");
    }
}

Game::~Game() {

}

bool Game::init() {
    //initialize var
    running = true;
    infoMode = false;
    frameCounter = 0;
    
    //initialize video
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Video Initialize failed! error code : %s\n", (SDL_GetError()));
        return 0;
    }

    //initialize window
    app.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (app.window == 0) {
        printf("Create window failed! error code : %s\n", (SDL_GetError()));
        return 0;
    }

    //initialize renderer
    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
    if (app.renderer == 0)
    {
        printf("Renderer Initialize failed! error code : %s\n", (SDL_GetError()));
        return 0;
    }

    //initialize IMG
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        printf("Image initialize failed! error code : %s\n", (IMG_GetError()));
        return 0;
    }

    //initialize TTF
    if (TTF_Init() != 0) {
        printf("Font initialize failed! error code : %s\n", TTF_GetError());
        return 0;
    }

    //initialize font
    app.font = TTF_OpenFont("src/font/HBIOS-SYS.ttf", 32);
    if (app.font == NULL) {
        printf("Failed to load font!\n");
        return 0;
    }

    printf("Game initialize Complete!\n");
    return 1;
}

void Game::gameLoop() {
    timer.program.start();
    object.init(app.renderer);
    while (running) {
        timer.frame.start();
        update();
        draw();
    }
}

void Game::draw() {
    SDL_RenderClear(app.renderer);
    object.draw(app.renderer);
    SDL_RenderPresent(app.renderer);
}

void Game::update() {
    //input calculate
    running = inputCalc(&input, timer.program.getTicks());

    object.update(&input);

    //frame calculate
    fps = frameCounter / (timer.frame.getTicks() / 1000.0f);
    int frameTicks = timer.frame.getTicks();
    if (frameTicks < SCREEN_TICK_PER_FRAME) {
        SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
    }
    frameCounter++;
}
