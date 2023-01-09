#include "font.h"

TTF_Font* Font::HBIOS_SYS_32 = NULL;
TTF_Font* Font::HBIOS_SYS_16 = NULL;

Font::~Font() {
	TTF_CloseFont(HBIOS_SYS_32);
	TTF_CloseFont(HBIOS_SYS_16);
}

bool Font::set() {
	HBIOS_SYS_32 = TTF_OpenFont("src/font/HBIOS-SYS.ttf", 32);
	HBIOS_SYS_16 = TTF_OpenFont("src/font/HBIOS-SYS.ttf", 16);
	if (HBIOS_SYS_32 && HBIOS_SYS_16) {
		printf("Font initialize Success!\n");
		return 1;
	}
	else {
		printf("Font initialize Failed!\n");
		return 0;
	}
}

TTF_Font* Font::get32() {
	return HBIOS_SYS_32;
}

TTF_Font* Font::get16() {
	return HBIOS_SYS_16;
}