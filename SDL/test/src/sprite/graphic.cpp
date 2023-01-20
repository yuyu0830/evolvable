#include "graphic.h"

Graphic* Graphic::create(int x, int y, const char fileDir[MAX_FRAME_NUMBER][20], int fileNum, bool _activate, int _frame) {
	Graphic* g = new Graphic();

	g->position.set(x, y);
	g->setFrameNull();
	for (int i = 0; i < fileNum; i++) {
		g->setTexture(fileDir[i], i);
	}
	g->activate = _activate;
	g->currentFrameNum = _frame;

	SDL_QueryTexture(g->frame[0], NULL, NULL, &g->size.width, &g->size.height);
	return g;
}


SDL_Texture* Graphic::getTexture() {
	return frame[currentFrameNum];
}

void Graphic::setTexture(const char* _fileDir, int _frameNum) {
	frame[_frameNum] = loadTexture(_fileDir);
}


bool Graphic::getActivate() {
	return activate;
}

void Graphic::setActivate() {
	activate = true;
}

void Graphic::setDisabled() {
	activate = false;
}


int Graphic::getFrameNum() {
	return currentFrameNum;
}

void Graphic::setFrameNum(int _frame) {
	currentFrameNum = _frame;
}

void Graphic::setFrameNull() {
	for (int i = 0; i < MAX_FRAME_NUMBER; i++) {
		frame[i] = NULL;
	}
}


Graphic::Graphic() {

}

Graphic::~Graphic() {
	printf("        Graphic ¼Ò¸êÀÚ ½ÃÀÛ!\n");
	for (int i = 0; i < frameNum; i++) {
		SDL_DestroyTexture(frame[i]);
	}
	printf("        Graphic ¼Ò¸êÀÚ ³¡!\n");
}