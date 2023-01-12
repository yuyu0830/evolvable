#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL_Image.h>

#include "../draw.h"
#include "../util.h"
#include "../position.h"


class Graphic {
public:
	~Graphic();
	static Graphic* create(
		int x,
		int y,
		const char fileDir[5][20],
		int fileNum,
		bool _activate = true,
		int _frame = 0
	);

	SDL_Texture* getTexture();

	bool getactivate();
	void setactivate();
	void setDisabled();

	int getFrame();
	void setFrame(int _frame);

	void setFrameNull();

	Position position; //Object Position 기준 위치
	Size size;

protected:
	SDL_Texture* frame[MAX_FRAME_NUMBER];
	int frameNum;
	int currentFrame;

	bool activate;
};

#endif