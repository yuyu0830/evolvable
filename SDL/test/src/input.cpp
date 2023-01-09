#include "input.h"
Uint32 Input::keys[255];
Uint32 Input::mouseClick[6];
Uint32 Input::mouseClicked[6];
SDL_Point Input::mousePosition;

Input::Input() {
    for (int i = 0; i < 255; i++) {
        keys[i] = 0;
    }
    for (int i = 0; i < 6; i++) {
        mouseClick[i] = 0;
        mouseClicked[i] = 0;
    }
    mousePosition = { 0, 0 };
}

bool Input::eventHandling() {
    Uint32 currentTime = Timer::getTicks(TIMER_PROGRAM);
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            return 0;
      
        //keyboard
        case SDL_KEYDOWN:
            keys[event.key.keysym.scancode] = currentTime;
            break;

        case SDL_KEYUP:
            keys[event.key.keysym.scancode] = 0;
            break;

            //mouse
        case SDL_MOUSEMOTION:
            mousePosition.x = event.motion.x;
            mousePosition.y = event.motion.y;
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouseClick[event.button.button] = currentTime;
            break;

        case SDL_MOUSEBUTTONUP:
            mouseClick[event.button.button] = 0;
            mouseClicked[event.button.button] = 0;
            break;
        }
    }
    return 1;
}

Uint32 Input::getKeys(SDL_Scancode key) {
    return keys[key];
}

Uint32 Input::getMouseClick(Uint8 button) {
    return mouseClick[button];
}

Uint32 Input::getMouseClicked(Uint8 button) {
    return mouseClicked[button];
}

SDL_Point Input::getMousePosition() {
    return mousePosition;
}