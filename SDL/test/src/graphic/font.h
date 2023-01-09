#ifndef FONT_H
#define FONT_H

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

class Font {
public:
	~Font();
	static bool set();
	static TTF_Font* get32();
	static TTF_Font* get16();

private:
	static TTF_Font* HBIOS_SYS_32;
	static TTF_Font* HBIOS_SYS_16;
};

#endif