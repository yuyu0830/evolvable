#ifndef PARTS_H
#define PARTS_H

#include <SDL_Image.h>

#include "graphic.h"

#include "../../util.h"

class Parts {
public:
	~Parts();
	void setCurrentFrame(int frame);
	void setTexture(SDL_Texture* _texture);

	SDL_Texture* getTexture();
	SDL_Rect getRect();

protected:
	int frameAmount;
	int currentFrameNumber;
	int maxFrameNumber;

	parts part;

	Size frameSize;
	SDL_Texture* texture;
};

#endif