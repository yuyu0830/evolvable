#ifndef UI_H
#define UI_H

#include "graphic.h"

class UI :public Graphic {
public:
	virtual void update();
	virtual void draw();

private:

};

#endif