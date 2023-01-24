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
		parts _part,
		const char fileDir[5][20],
		int fileNum,
		bool _activate = true
	);

	SDL_Texture* getTexture(int _frameNum);
	void setTexture(const char* _fileDir, int _frameNum);

	bool getActivate();
	void setActivate();
	void setDisabled();

	void setFrameNull();

	Position position; //Object Position 기준 위치
	Size size;

protected:
	SDL_Texture* frame[MAX_FRAME_NUMBER];

	parts part;

	int frameNum; // 프레임 개수

	bool activate;
};

#endif