#ifndef UI_H
#define UI_H

#include <SDL_ttf.h>

#include "object.h"

#include "../../font.h"

class UI : public Object {
public:
	virtual void update() = 0;

private:

};

#endif