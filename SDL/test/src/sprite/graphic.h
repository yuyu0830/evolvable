#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL_Image.h>

#include "../draw.h"
#include "../util.h"
#include "../position.h"


class Graphic {
public:
	Graphic();
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
	void setTexture(const char* _fileDir, int _frameNum);

	bool getActivate();
	void setActivate();
	void setDisabled();

	int getFrameNum();
	void setFrameNum(int _frameNum);

	void setFrameNull();

	Position position; //Object Position 기준 위치
	Size size;

protected:
	SDL_Texture* frame[MAX_FRAME_NUMBER];

	int frameNum;
	int currentFrameNum;

	bool activate;
};

#endif