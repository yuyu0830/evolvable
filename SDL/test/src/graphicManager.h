#ifndef GRAPHICMANAGER_H
#define GRAPHICMANAGER_H

#include "util.h"

#include "sprite/graphic.h"

class GraphicManager {
public:
	GraphicManager();
	static Graphic* getGraphic(parts part);
	
	static bool checkGraphic(parts part);

	static void loadGraphic(parts part);
	static void loadGraphic(parts part[]);

	static void deleteGraphic(parts part);
	static void deleteGraphic(parts part[]);

	static void deleteAllGraphic();

private:
	static Graphic* graphic[PARTSNUM];
};
#endif