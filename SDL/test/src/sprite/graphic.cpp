#include "graphic.h"

Graphic* Graphic::create(int x, int y, parts part[], int _frameAmount, bool _activate, int _currentFrameNum) {
	Graphic* g = new Graphic();
	
	g->position.set(x, y);
	g->setFrameNull();
	for (int i = 0; i < _frameAmount; i++) {
		g->frame[i] = GraphicManager::get(part[i]);
	}
	g->activate = _activate;
	g->frameAmount = _frameAmount;
	g->currentFrameNum = _currentFrameNum;

	SDL_QueryTexture(g->frame[0], NULL, NULL, &g->size.width, &g->size.height);
	return g;
}


SDL_Texture* Graphic::getTexture() {
	return frame[currentFrameNum];
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


void Graphic::setFrameNull() {
	for (int i = 0; i < MAX_FRAME_NUMBER; i++) {
		frame[i] = NULL;
	}
}


Graphic::Graphic() {

}

Graphic::~Graphic() {
	printf("        Graphic ¼Ò¸êÀÚ ½ÃÀÛ!\n");
	for (int i = 0; i < frameAmount; i++) {
		frame[i] = NULL;
	}
	delete[] frame;
	printf("        Graphic ¼Ò¸êÀÚ ³¡!\n");
}