#ifndef TEXT_H
#define TEXT_H

#include <string>

#include <SDL.h>

#include "../util.h"

class Text {
public:

private:
	SDL_Texture* textTexture;
	std::string text;

};

#endif