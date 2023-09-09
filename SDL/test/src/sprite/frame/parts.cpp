#include "parts.h"

void Parts::setCurrentFrame(int frame) {
	if (frame > maxFrameNumber) {
		printf("Frame Set ERROR!!\n");
	}
	else {
		currentFrameNumber = frame;
	}
}

void Parts::setTexture(SDL_Texture* _texture) {
	texture = _texture;
}

SDL_Texture* Parts::getTexture() {
	return texture;
}

SDL_Rect Parts::getRect() {
	SDL_Rect rect = { (currentFrameNumber - 1) * frameSize.w, 0, frameSize.w, frameSize.h };
}

Parts::~Parts() {
	texture = NULL;
}