#ifndef DRAW_H
#define DRAW_H

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

void drawTexture(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture);
void drawTextureOption(SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dst, SDL_Texture* texture);
void drawTextureEx(SDL_Renderer* renderer, int x, int y, float angle, SDL_Texture* texture);
void drawTextureExOption(SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dst, float angle, SDL_Texture* texture);

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* file);
SDL_Texture* textToTexture(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color);

#endif