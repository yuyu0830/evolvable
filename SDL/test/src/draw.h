#ifndef DRAW_H
#define DRAW_H

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

void drawTexture(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture);
void drawTextureOption(SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dst, SDL_Texture* texture);
void drawTextureEx(SDL_Renderer* renderer, int x, int y, float angle, SDL_Texture* texture);
void drawTextureExOption(SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dst, float angle, SDL_Texture* texture);

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* file);

#endif