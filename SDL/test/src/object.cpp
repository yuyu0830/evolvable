#include "object.h"

Object::~Object() {
    delete unit[0];
    delete unit[1];
    delete input;

    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
}

bool Object::init(SDL_Window* window) {
    //Initialize variable
    background = NULL;

    //Initialize input struct
    input = new Input;
    for (int i = 0; i < 255; i++) {
        input->keys[i] = false;
    }
    for (int i = 0; i < 3; i++) {
        input->mouseClick[i] = false;
        input->mouseClicked[i] = false;
    }
    input->mousePos = { 0, 0 };
    printf("Input Struct Initialize Complete!\n");

    //initialize renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer != NULL) { return 1; }
    else { return 0; }
}

void Object::tmp() {
    unit[0] = new Player(2);
    unit[1] = new Unit();

    objectData a;
    strcpy_s(a.name, "Player");
    a.tag = 1;
    a.unitNum = 1;
    unit[0]->load(a, renderer, "src/image/Player.png", { 300, 100, 0, 0 });

    strcpy_s(a.name, "enemy");
    a.tag = 2;
    a.unitNum = 2;
    unit[1]->load(a, renderer, "src/image/bullet.png", { 600, 100, 0, 0 });
}

int Object::update() {
    if (eventHandling()) {
        for (int i = 0; i < 2; i++) {
            unit[i] -> update(input);
        }
        return 1;
    }
    else {
        return 0;
    }
}

int Object::draw() {
    //SDL_RenderClear(renderer);
    for (int i = 0; i < 2; i++) {
        unit[i] -> draw(renderer);
    }
    SDL_RenderPresent(renderer);
    return 0;
}

bool Object::eventHandling() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) return 0;
        switch (event.type) {
            //keyboard
        case SDL_KEYDOWN:
            //printf("%d\n", event.key.keysym.scancode);
            input->keys[event.key.keysym.scancode] = true;
            break;

        case SDL_KEYUP:
            input->keys[event.key.keysym.scancode] = 0;
            break;

            //mouse
        case SDL_MOUSEMOTION:
            input->mousePos.x = event.motion.x;
            input->mousePos.y = event.motion.y;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                input->mouseClick[0] = true;
            }
            else if (event.button.button == SDL_BUTTON_RIGHT) {
                input->mouseClick[1] = true;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                input->mouseClick[0] = 0;
                input->mouseClicked[0] = false;
            }
            else if (event.button.button == SDL_BUTTON_RIGHT) {
                input->mouseClick[1] = 0;
                input->mouseClicked[1] = false;
            }
            break;
        }
    }
    return 1;
}