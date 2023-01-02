#include "UI.h"

void UI::load(SDL_Renderer* renderer, const char* fileDir, const char* onMouseFileDir, ObjectData data, TextContainer tc) {
	onMouse = false;

	texture = loadTexture(renderer, fileDir);
	onMouseTexture = loadTexture(renderer, onMouseFileDir);
	SDL_QueryTexture(texture, NULL, NULL, &size.width, &size.height);

	strcpy_s(name, data.name);
	tag = data.tag;
	unitNum = data.unitNum;

	strcpy_s(text, tc.text);
	textColor = tc.color;
	font = tc.font;
	//TTF_SizeText(font, text, &textSize.width, &textSize.height);
	textTexture = textToTexture(renderer, font, text, textColor);
	SDL_QueryTexture(textTexture, NULL, NULL, &textSize.width, &textSize.height);
}

void UI::update(Input* input) {
	int cnt = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j <= 3; j += 3) {
			if ((vertex[i + j].y > input->mousePos.y) != (vertex[i + j + 1].y > input->mousePos.y)) {
				double atX = (vertex[i + j + 1].x - vertex[i + j].x) * (input->mousePos.y - vertex[i + j].y) / (vertex[i + j + 1].y - vertex[i + j].y) + vertex[i + j].x;
				if (input->mousePos.x < atX)
					cnt++;
			}
		}
	}

	if (cnt == 1) {
		onMouse = true;
	}
	else {
		onMouse = false;
	}
}

void UI::draw(SDL_Renderer* renderer) {
	SDL_FPoint pos = position.get();
	if (onMouse) {
		drawTexture(renderer, (int)(pos.x - size.width / 2), (int)(pos.y - size.height / 2), onMouseTexture);
	}
	else {
		drawTexture(renderer, (int)(pos.x - size.width / 2), (int)(pos.y - size.height / 2), texture);
	}
	drawTexture(renderer, (int)(pos.x - textSize.width / 2), (int)(pos.y - textSize.height / 2), textTexture);
} 

void UI::vertexCalc() {
	SDL_FPoint pos = position.get();
	vertex[0] = { (int) pos.x + 59, (int) pos.y - 102 };
	vertex[1] = { (int)pos.x + 118, (int)pos.y};
	vertex[2] = { (int)pos.x + 59, (int)pos.y + 102 };
	vertex[3] = { (int)pos.x - 59, (int)pos.y + 102 };
	vertex[4] = { (int)pos.x - 118, (int)pos.y};
	vertex[5] = { (int)pos.x - 59, (int)pos.y - 102 };
}