#ifndef PARTSMANAGER_H
#define PARTSMANAGER_H

#include "graphic.h"
#include "parts.h"

#include "../../util.h"

class PartsManager {
public:
	PartsManager();

	static Parts* load(parts part);

	static void unload(parts part);

	static void unloadAll();

private:
	static SDL_Texture* texture[PARTS_AMOUNT];
};
#endif