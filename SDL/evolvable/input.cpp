#include "input.h"

void inputCal(SDL_Event event) {
    switch (event.type) {
    case SDL_KEYDOWN:
        //printf("%d\n", event.key.keysym.scancode);
        //keys[event.key.keysym.scancode] = true;
        /*if (event.key.keysym.scancode == 60) {
            developerMode = !developerMode;
        }
        if (event.key.keysym.scancode == 59) {
            moveMode = !moveMode;
        }*/
        break;
   /* case SDL_KEYUP:
        keys[event.key.keysym.scancode] = false;
        break;
    case SDL_MOUSEMOTION:
        mouse.pos.x = event.motion.x;
        mouse.pos.y = event.motion.y;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
            mouse.click[0] = true;
        }
        else if (event.button.button == SDL_BUTTON_RIGHT) {
            mouse.click[1] = true;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT) {
            mouse.click[0] = false;
            mouse.clicked[0] = false;
        }
        else if (event.button.button == SDL_BUTTON_RIGHT) {
            mouse.click[1] = false;
            mouse.clicked[1] = false;
        }
        break;*/
    }
}