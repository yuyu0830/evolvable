#ifndef UI_H
#define UI_H

#include <SDL_ttf.h>

#include "graphic.h"

class UI : public Graphic {
public:
	UI(ObjectData data, TextContainer tc, SDL_Renderer* renderer, SDL_Texture* defaultButton, SDL_Texture* onMouseButton, SDL_Point _position);
	~UI();
	void update();
	void draw();

	//반복 사용
	bool isOnMouse();

	//한번 사용
	void textDataInput(TextContainer tc);
	void imageInput(SDL_Renderer* renderer, SDL_Texture* defaultButton, SDL_Texture* onMouseButton);
	void vertexCalc(SDL_Point _position);
	

private:
	SDL_Texture* defaultButton;
	SDL_Texture* onMouseButton;
	SDL_Point vertex[6];
	bool onMouse;
	bool isClickable;

	//text
	TTF_Font* font;
	Size textSize;
	SDL_Texture* textTexture;
	SDL_Color textColor;
	char text[20];
};

#endif