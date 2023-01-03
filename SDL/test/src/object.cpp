#include "object.h"

Object::~Object() {
    SDL_DestroyRenderer(renderer);
}

bool Object::init(SDL_Window* window) {
    //Initialize variable
    for (int i = 0; i < SHAPE_NUMBER; i++) {
        for (int j = 0; j < SHAPE_NUMBER; j++) {
            colliderTriggerTable[i][j] = false;
        }
    }
    
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

    //initialize renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //tmp#############################################################
    //tmpFont = TTF_OpenFont("src/font/HBIOS-SYS.ttf", 32);

    background.load(renderer, "./src/image/MainBg.png");
    //button[0].load(renderer, "./src/image/Button_default.png", "./src/image/Button_onMouse.png", { "button1", TAG_UI, 1 }, { COLOR_BLACK, tmpFont, "New Game" });
    //button[0].position.set(779, 621);
    //button[0].vertexCalc();
    //button[1].load(renderer, "./src/image/Button_default.png", "./src/image/Button_onMouse.png", { "button2", TAG_UI, 2 }, { COLOR_BLACK, tmpFont, "Load Game" });
    //button[1].position.set(966, 513);
    //button[1].vertexCalc();
    //button[2].load(renderer, "./src/image/Button_default.png", "./src/image/Button_onMouse.png", { "button3", TAG_UI, 3 }, { COLOR_BLACK, tmpFont, "Option" });
    //button[2].position.set(1154, 621);
    //button[2].vertexCalc();
    //button[3].load(renderer, "./src/image/Button_default.png", "./src/image/Button_onMouse.png", { "button4", TAG_UI, 4 }, { COLOR_BLACK, tmpFont, "Exit" });
    //button[3].position.set(1341, 513);
    //button[3].vertexCalc();
    //player.load(renderer, "./src/image/Player.png", { "Player", TAG_PLAYER, 1}, { false, 1.f, 1.f, 1.f, 1.f });
    //tmp#############################################################

    if (renderer != NULL) { return 1; }
    else { return 0; }
}

int Object::update() {
    if (eventHandling()) {
        //player.update(input);
        return 1;
    }
    else {
        return 0;
    }
}

int Object::draw() {
    SDL_RenderClear(renderer);
    background.draw(renderer);
    //player.draw(renderer);
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