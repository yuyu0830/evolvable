#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL_Image.h>

#include "../draw.h"
#include "../util.h"
#include "../graphicManager.h"
#include "../position.h"

class Graphic {
public:
	Graphic();
	~Graphic();
	static Graphic* create(
		int x,
		int y,
		parts part[],
		int _frameAmount,
		bool _activate = true,
		int _currentFrameNum = 0
	);

	SDL_Texture* getTexture();

	bool getActivate();
	void setActivate();
	void setDisabled();

	void setFrameNull();

	Position position; //Object Position 기준 위치
	Size size;

protected:
	SDL_Texture* frame[MAX_FRAME_NUMBER];

	int frameAmount; // 프레임 개수
	int currentFrameNum;

	bool activate;
};

#endif