#ifndef UI_H
#define UI_H

#include <SDL_ttf.h>

#include "../object.h"
#include "../font.h"

class UI : public Object{
public:
	UI(int x, int y, type _type, const char* _text) : Object(x, y, _type) {
		isOnMouse = false;
		UINum = staticUINum++;
	};

	~UI();

	void update();

private:

	int UINum;
	static int staticUINum;
	bool isOnMouse;
};

#endif