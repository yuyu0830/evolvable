#include "graphic.h"

Graphic* Graphic::create(int x, int y, const char fileDir[MAX_FRAME_NUMBER][20], int fileNum, bool _activate, int _frame) {
	Graphic* g = new Graphic();


	g->position.set(x, y);
	g->setFrameNull();

	g->activate = _activate;
	g->currentFrame = _frame;


	SDL_QueryTexture(g->frame[0], NULL, NULL, &g->size.width, &g->size.height);
	return g;
}

SDL_Texture* Graphic::getTexture() {
	return frame[currentFrame];
}

bool Graphic::getactivate() {
	return activate;
}

void Graphic::setactivate() {
	activate = true;
}

void Graphic::setDisabled() {
	activate = false;
}

int Graphic::getFrame() {
	return currentFrame;
}

void Graphic::setFrame(int _frame) {
	currentFrame = _frame;
}

void Graphic::setFrameNull() {
	for (int i = 0; i < MAX_FRAME_NUMBER; i++) {
		frame[i] = NULL;
	}
}

Graphic::~Graphic() {
	for (int i = 0; i < frameNum; i++) {
		SDL_DestroyTexture(frame[i]);
	}
}