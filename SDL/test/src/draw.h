#ifndef DRAW_H
#define DRAW_H

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "graphic/renderer.h"

void drawTexture(int x, int y, SDL_Texture* texture);
void drawTextureOption(SDL_Rect src, SDL_Rect dst, SDL_Texture* texture);

void drawTextureEx(int x, int y, float angle, SDL_Texture* texture);
void drawTextureExOption(SDL_Rect src, SDL_Rect dst, float angle, SDL_Texture* texture);

SDL_Texture* loadTexture(const char* file);
SDL_Texture* textToTexture(TTF_Font* font, const char* text, SDL_Color color);

#endif