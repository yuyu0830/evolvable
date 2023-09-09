#ifndef DRAW_H
#define DRAW_H

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "renderer.h"

void drawTexture(int x, int y, SDL_Rect src, SDL_Texture* texture);
void drawTexture(SDL_FPoint pos, SDL_Rect src, SDL_Texture* texture);

void drawTextureEx(int x, int y, SDL_Rect src, float angle, SDL_Texture* texture);
void drawTextureEx(SDL_FPoint pos, SDL_Rect src, float angle, SDL_Texture* texture);

SDL_Texture* loadTexture(const char* file);
SDL_Texture* textToTexture(TTF_Font* font, const char* text, SDL_Color color);

#endif