#include "UI.h"
//
//int UI::staticUINum;
//
//void UI::update() {
//	SDL_Point vertex[6];
//
//	vertex[0] = { (int)position.getX() + 59, (int)position.getY() - 102 };
//	vertex[1] = { (int)position.getX() + 118, (int)position.getY() };
//	vertex[2] = { (int)position.getX() + 59, (int)position.getY() + 102 };
//	vertex[3] = { (int)position.getX() - 59, (int)position.getY() + 102 };
//	vertex[4] = { (int)position.getX() - 118, (int)position.getY() };
//	vertex[5] = { (int)position.getX() - 59, (int)position.getY() - 102 };
//
//	int cnt = 0;
//	SDL_Point mouse = Input::getMousePosition();
//	for (int i = 0; i < 2; i++) {
//		for (int j = 0; j <= 3; j += 3) {
//			if ((vertex[i + j].y > mouse.y) != (vertex[i + j + 1].y > mouse.y)) {
//				double atX = (vertex[i + j + 1].x - vertex[i + j].x) * (mouse.y - vertex[i + j].y) / (vertex[i + j + 1].y - vertex[i + j].y) + vertex[i + j].x;
//				if (mouse.x < atX)
//					cnt++;
//			}
//		}
//	}
//
//	if (cnt == 1) {
//		isOnMouse = true;
//		graphicFrameNum[0] = 1;
//	}
//	else {
//		isOnMouse = false;
//		graphicFrameNum[0] = 0;
//	}
//}
//
//
//UI::~UI() {
//	printf("UI %d ¼Ò¸êÀÚ ½ÃÀÛ!\n", UINum);
//	printf("UI %d ¼Ò¸êÀÚ ³¡!\n", UINum);
//}
