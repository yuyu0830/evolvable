#include "game.h"

Game::Game() {
    //Initialize Game and Start Game!
    if (this->init()) {
        this->gameLoop();
    }
    else {
        printf("Please try again...\n");
    }
}

void Game::gameLoop() {
    while (running) {
        Timer::start(TIMER_FRAME);

        update();
        draw();

        Timer::frameSynchronization();
    }
}



int Game::update() {
    if (!Input::eventHandling()) {
        running = false;
        return 0;
    }

    return 0;
}

int Game::draw() {
    SDL_RenderClear(Renderer::getInstance()->getRenderer());
    //background.draw();
    SDL_RenderPresent(Renderer::getInstance()->getRenderer());
    return 0;
}

bool Game::init() {
    // ##############################################################################################
    // Library Initialize
    // initialize video library
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        printf("SDL library Initialize Success!\n");
    }
    else {
        printf("SDL library Initialize failed! error code : %s\n", (SDL_GetError()));
        return 0;
    }

    // initialize IMG library
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == IMG_INIT_PNG) {
        printf("Image library Initialize Success!\n");
    }
    else {
        printf("Image library Initialize failed! error code : %s\n", (IMG_GetError()));
        return 0;
    }

    // initialize TTF library
    if (TTF_Init() == 0) {
        printf("Font library Initialize Success!\n");
    }
    else {
        printf("Font library initialize failed! error code : %s\n", TTF_GetError());
        return 0;
    }


    // ##############################################################################################
    // Class Initialize
    // initialize renderer
    if (!Renderer::getInstance()->set()) { return 0; }

    // initialize font
    if (!Font::set()) { return 0; }

    tmpset();


    Timer::start(TIMER_PROGRAM);

    running = true;
    srand(time(NULL));

    printf("Game initialize Complete!\n");
    return 1;
}

void Game::tmpset() {

}