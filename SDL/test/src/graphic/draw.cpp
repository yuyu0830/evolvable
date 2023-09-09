#include "draw.h"

void drawTexture(int x, int y, SDL_Rect src, SDL_Texture* texture) {
    SDL_Rect dst;

    dst.x = x;
    dst.y = y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(Renderer::getInstance()->getRenderer(), texture, &src, &dst);
}

void drawTexture(SDL_FPoint pos, SDL_Rect src, SDL_Texture* texture) {
    SDL_Rect dst;

    dst.x = pos.x;
    dst.y = pos.y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(Renderer::getInstance()->getRenderer(), texture, &src, &dst);
}

void drawTextureEx(int x, int y, SDL_Rect src, float angle, SDL_Texture* texture) {
    SDL_Rect dst;
    SDL_Point center;

    dst.x = x;
    dst.y = y;
    dst.w = src.w;
    dst.h = src.h;
    center.x = dst.w / 2;
    center.y = src.h / 2;
    SDL_RenderCopyEx(Renderer::getInstance()->getRenderer(), texture, &src, &dst, angle, &center, SDL_FLIP_NONE);
}

void drawTextureEx(SDL_FPoint pos, SDL_Rect src, float angle, SDL_Texture* texture) {
    SDL_Rect dst;
    SDL_Point center;

    dst.x = pos.x;
    dst.y = pos.y;
    dst.w = src.w;
    dst.h = src.h;
    center.x = dst.w / 2;
    center.y = src.h / 2;
    SDL_RenderCopyEx(Renderer::getInstance()->getRenderer(), texture, &src, &dst, angle, &center, SDL_FLIP_NONE);
}

SDL_Texture* loadTexture(const char* file) {
    SDL_Surface* surface;
    SDL_Texture* texture;
    char dir[50] = "image\\";
    strcat_s(dir, file);
    strcat_s(dir, ".png");
    surface = IMG_Load(dir);
    if (surface == NULL) {
        printf("fail to read %s\n", file);
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(Renderer::getInstance()->getRenderer(), surface);
    if (texture == NULL)  printf("unable to create texture.\n");
    SDL_FreeSurface(surface);

    return texture;
}

SDL_Texture* textToTexture(TTF_Font* font, const char* text, SDL_Color color) {
    SDL_Surface* surface;
    SDL_Texture* texture;

    surface = TTF_RenderText_Blended(font, text, color);
    if (surface == NULL) {
        printf("fail to make surface with text '%s'\n", text);
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(Renderer::getInstance()->getRenderer(), surface);
    if (texture == NULL)  printf("unable to create texture.\n");
    SDL_FreeSurface(surface);

    return texture;
}