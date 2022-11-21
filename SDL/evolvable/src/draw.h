#ifndef DRAW_H_
#define DRAW_H_

#include <ostream>

#include <SDL.h>
#include <SDL_image.h>

void drawTexture(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture);
void drawTextureR(SDL_Renderer* renderer, int x, int y, float angle, SDL_Texture* texture);
void drawTextureA(SDL_Renderer* renderer, SDL_Rect src, int x, int y, SDL_Texture* texture);
void drawTextureB(SDL_Renderer* renderer, SDL_Rect dst, SDL_Texture* texture);
void drawTextureAR(SDL_Renderer* renderer, SDL_Rect src, int x, int y, float angle, SDL_Texture* texture);
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* file);

#endif