#ifndef GRAPHICMANAGER_H
#define GRAPHICMANAGER_H

#include "util.h"

#include "sprite/graphic.h"

class GraphicManager {
public:
	GraphicManager();
	~GraphicManager();
	static SDL_Texture* get(parts part);
	
	static bool check(parts part);

	static void load(parts part);

	static void unload(parts part);

	static void unloadAll();

private:
	static SDL_Texture* texture[PARTSNUM];
};
#endif