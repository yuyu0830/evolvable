#pragma once

#include "game.h"

void drawTexture(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture);
void drawTextureR(SDL_Renderer* renderer, int x, int y, float angle, SDL_Texture* texture);
void drawTextureA(SDL_Renderer* renderer, SDL_Rect src, int x, int y, SDL_Texture* texture);
void drawTextureAR(SDL_Renderer* renderer, SDL_Rect src, int x, int y, float angle, SDL_Texture* texture);