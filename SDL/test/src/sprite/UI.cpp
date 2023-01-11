#include "UI.h"

void UI::update() {

}

void UI::draw() {
	SDL_FPoint pos = position.get();
	if (onMouse) {
		drawTexture((int)(pos.x - size.width / 2), (int)(pos.y - size.height / 2), onMouseButton);
	}
	else {
		drawTexture((int)(pos.x - size.width / 2), (int)(pos.y - size.height / 2), defaultButton);
	}
	drawTexture((int)(pos.x - textSize.width / 2), (int)(pos.y - textSize.height / 2), textTexture);
}

//###############################################################################################
//initailize

UI::UI(ObjectData data, TextContainer tc, SDL_Renderer* renderer, SDL_Texture* _defaultButton, SDL_Texture* _onMouseButton, SDL_Point _position) {
	onMouse = false;
	
	dataInput(data);
	textDataInput(tc);
	imageInput(renderer, _defaultButton, _onMouseButton);
}

void UI::textDataInput(TextContainer tc) {
	strcpy_s(text, tc.text);
	textColor = tc.color;
	font = tc.font;
}

void UI::imageInput(SDL_Renderer* renderer, SDL_Texture* _defaultButton, SDL_Texture* _onMouseButton) {
	defaultButton = _defaultButton;
	onMouseButton = _onMouseButton;

	SDL_QueryTexture(defaultButton, NULL, NULL, &size.width, &size.height);

	textTexture = textToTexture(font, text, textColor);
	SDL_QueryTexture(textTexture, NULL, NULL, &textSize.width, &textSize.height);

}

void UI::vertexCalc(SDL_Point _position) {
	position.set(_position);

	vertex[0] = { (int)_position.x + 59, (int)_position.y - 102 };
	vertex[1] = { (int)_position.x + 118, (int)_position.y };
	vertex[2] = { (int)_position.x + 59, (int)_position.y + 102 };
	vertex[3] = { (int)_position.x - 59, (int)_position.y + 102 };
	vertex[4] = { (int)_position.x - 118, (int)_position.y };
	vertex[5] = { (int)_position.x - 59, (int)_position.y - 102 };
}


//###############################################################################################


//bool UI::isOnMouse(Input* input) {
//	// 점의 다각형 내부 외부 판단 알고리즘
//	int cnt = 0;
//	for (int i = 0; i < 2; i++) {
//		for (int j = 0; j <= 3; j += 3) {
//			if ((vertex[i + j].y > input->mousePos.y) != (vertex[i + j + 1].y > input->mousePos.y)) {
//				double atX = (vertex[i + j + 1].x - vertex[i + j].x) * (input->mousePos.y - vertex[i + j].y) / (vertex[i + j + 1].y - vertex[i + j].y) + vertex[i + j].x;
//				if (input->mousePos.x < atX)
//					cnt++;
//			}
//		}
//	}
//	printf("%d\n", cnt);
//	if (cnt == 1) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}


UI::~UI() {
	SDL_DestroyTexture(defaultButton);
	SDL_DestroyTexture(onMouseButton);
	SDL_DestroyTexture(textTexture);
	TTF_CloseFont(font);
}
