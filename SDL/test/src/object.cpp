#include "object.h"


int Object::update() {
    if (eventHandling()) {
        if (isInGame) {

        }
        else {

        }
        return 1;
    }
    else {
        return 0;
    }
}

int Object::draw() {
    SDL_RenderClear(renderer);

    if (isInGame) {

    }
    else {

    }

    SDL_RenderPresent(renderer);
    return 0;
}

void Object::collisionCheck() {
    if (isInGame) {
        
    }
    else {

    }
}

bool Object::eventHandling() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
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
            /*if (event.button.button == SDL_BUTTON_LEFT) {
                input->mouseClick[0] = true;
            }
            else if (event.button.button == SDL_BUTTON_RIGHT) {
                input->mouseClick[1] = true;
            }*/
            input->mouseClick[event.button.button] = true;
            break;

        case SDL_MOUSEBUTTONUP:
            /*if (event.button.button == SDL_BUTTON_LEFT) {
                input->mouseClick[0] = 0;
                input->mouseClicked[0] = false;
            }
            else if (event.button.button == SDL_BUTTON_RIGHT) {
                input->mouseClick[1] = 0;
                input->mouseClicked[1] = false;
            }*/
            input->mouseClick[event.button.button] = false;
            input->mouseClicked[event.button.button] = false;
            break;
        }
    }
    return 1;
}

bool Object::init(SDL_Window* window) {
    //Initialize variable
    initVariable();

    //Initialize input struct
    initInput();

    //initialize renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //tmp#############################################################
    
    //tmp#############################################################

    if (renderer != NULL) { return 1; }
    else { return 0; }
}

void Object::initVariable() {
    isInGame = false;

    for (int i = 0; i < TAG_NUMBER; i++) {
        for (int j = 0; j < TAG_NUMBER; j++) {
            colliderTriggerTable[i][j] = false;
        }
    }
}

void Object::initInput() {
    input = new Input;
    for (int i = 0; i < 255; i++) {
        input->keys[i] = false;
    }
    for (int i = 0; i < 6; i++) {
        input->mouseClick[i] = false;
        input->mouseClicked[i] = false;
    }
    input->mousePos = { 0, 0 };
}

Object::~Object() {
    SDL_DestroyRenderer(renderer);
    delete input;
    //delete[] graphic;
}