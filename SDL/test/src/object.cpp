#include "object.h"

bool Object::init(SDL_Window* window) {
    //initialize renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer != NULL) { return 1; }
    else { return 0; }
}

void Object::tmp() {
    printf("tmp start\n");
    printf("tmp end\n");
}

void Object::update() {

}

void Object::draw() {
    SDL_RenderPresent(renderer);
}