#include "object.h"

Object::~Object() {
    delete[] unit;
    delete input;
}

bool Object::init(SDL_Window* window) {
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
    unit = new Unit[20];
    objectData a;
    strcpy_s(a.name, "unit");
    for (int i = 0; i < 20; i++) {
        a.tag = 1;
        a.unitNum = i;
        unit[i].load(a, renderer, "src/image/Player.png", { i * 20, i * 20, 0, 0 });
    }
}

int Object::update() {
    if (eventHandling()) {
        for (int i = 0; i < 20; i++) {
            unit[i].update();
        }
    }
    else {
        return 0;
    }
}

int Object::draw() {
    for (int i = 0; i < 20; i++) {
        unit[i].draw(renderer);
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