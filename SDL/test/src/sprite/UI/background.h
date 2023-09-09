#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../frame/graphic.h"

#include "../../graphic/renderer.h"

class Background : public Graphic {
public:
	Background();
	void setColor(SDL_Color _color);
	void setOpacity(int _opacity);
	void setWindowSize(int width, int height);
	void draw();
		
protected:
	SDL_Color color;
	SDL_Rect window;
	int opacity;
};

#endif