#include "src/input.h"

bool inputCalc(Input* input, Uint32 programTime) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) return 0;
        switch (event.type) {
        //keyboard
        case SDL_KEYDOWN:
            //printf("%d\n", event.key.keysym.scancode);
            input -> keys[event.key.keysym.scancode] = programTime;
            break;

        case SDL_KEYUP:
            input -> keys[event.key.keysym.scancode] = 0;
            break;


        //mouse
        case SDL_MOUSEMOTION:
            input -> mousePos.x = event.motion.x;
            input -> mousePos.y = event.motion.y;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                input -> mouseClick[0] = programTime;
            }
            else if (event.button.button == SDL_BUTTON_RIGHT) {
                input -> mouseClick[1] = programTime;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                input->mouseClick[0] = 0;
            }
            else if (event.button.button == SDL_BUTTON_RIGHT) {
                input->mouseClick[1] = 0;
            }
            break;
        }
	}
}