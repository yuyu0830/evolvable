#include "object.h"

int Object::update() {
    if (Input::eventHandling()) {
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
    SDL_RenderClear(Renderer::getInstance()->getRenderer());
    if (!isInGame) {
        menu->draw();
    }
    else {

    }

    SDL_RenderPresent(Renderer::getInstance()->getRenderer());
    return 0;
}

void Object::collisionCheck() {
    if (isInGame) {
        
    }
    else {

    }
}

void Object::init() {
    //Initialize variable
    initVariable();
    menu = new Menu();
}

void Object::initVariable() {
    isInGame = false;

    for (int i = 0; i < TAG_NUMBER; i++) {
        for (int j = 0; j < TAG_NUMBER; j++) {
            colliderTriggerTable[i][j] = false;
        }
    }
}