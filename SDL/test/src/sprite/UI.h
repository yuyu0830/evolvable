#ifndef UI_H
#define UI_H

#include <SDL_ttf.h>

#include "graphic.h"

class UI : public Graphic {
public:
	~UI();
	virtual void load(SDL_Renderer* renderer, const char* fileDir, const char* onMouseFileDir, ObjectData data , TextContainer tc);
	virtual void update(Input* input);
	virtual void draw(SDL_Renderer* renderer);
	void vertexCalc();
	bool isOnMouse(Input* input);

private:
	SDL_Texture* onMouseTexture;
	SDL_Point vertex[6];
	bool onMouse;

	//text
	TTF_Font* font;
	Size textSize;
	SDL_Texture* textTexture;
	SDL_Color textColor;
	char text[20];
};

#endif