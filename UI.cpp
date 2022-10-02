#include "RPManager.h"

void unZip(string, string);
void change(initData, int);
void gotoxy(int, int);
COORD getCursorPos();
bool keyDown(int);
bool outputWF(string, int, int);
bool setTextColor(int);
bool keyDown(int);

extern bool UI(initData input)
{
	// draw frame
	gotoxy(0, 0);
	outputWF("RPManager\\frameTop.texX", 0, -1);
	for (int i = 1; i < 28; ++i) {
		gotoxy(0, i);
		outputWF("RPManager\\frameBody.texX", 0, -1);
	}
	gotoxy(2, 25);
	outputWF("RPManager\\helpInfo.texX", 0, -1);
	gotoxy(2, 26);
	outputWF("RPManager\\helpInfoln2.texX", 0, -1);
	gotoxy(2, 27);
	outputWF("RPManager\\helpInfoln3.texX", 0, -1);
	gotoxy(0, 28);
	outputWF("RPManager\\frameBottom.texX", 0, -1);
	
	setTextColor(ESC_COLOR_RANDOM);
	gotoxy(40, 3);
	cout << "0\t<RESET TO DEFAULT>";
	if (input.resourcepacks.size() == 0) {
		gotoxy(20, 10);
		cout << "<NOT ANY RESOURCEPACKS HAS BEEN FOUND IN FOLLOWING DICTIONARY>";
	}
	for (int i = 0; i < min(20, input.resourcepacks.size()); ++i) {
		gotoxy(40, i+4);
		cout << i + 1 << "\t" << input.resourcepacks[i];
	}

	int pointer = 0;
	bool flag = false;
	if (input.config.RPNow != "ORIG") {
		for (int i = 0; i < input.resourcepacks.size(); ++i) {
			if (input.resourcepacks[i] == input.config.RPNow) {
				pointer = i + 1;
				flag = true;
				break;
			}
		}
		if (!flag) {
			pointer = 0;
			change(input, -1);
			return true;
		}
	}
	gotoxy(20, pointer + 3);
	printf("[=>");

	flag = true;
	bool redraw = true;
	bool Up = false, Dn = false, SPACE = false;
	while (flag) {
		if (redraw == true) {
			for (int i = 0; i <= 20; ++i) {
				gotoxy(25, i + 2);
				printf("          ");
			}
			gotoxy(25, pointer + 3);
			printf("=========>");
			redraw = false;
		}
		if (!(keyDown(VK_UP) || keyDown(VK_LEFT))) {
			Up = true;
		}
		if (!(keyDown(VK_DOWN) || keyDown(VK_RIGHT))) {
			Dn = true;
		}
		if (!keyDown(VK_SPACE)) {
			SPACE = true;
		}
		if ((keyDown(VK_UP) || keyDown(VK_LEFT)) && Up) {
			if (pointer != 0) {
				--pointer;
			}
			else {
				pointer = int(input.resourcepacks.size());
			}
			redraw = true;
			Up = false;
		}
		if ((keyDown(VK_DOWN) || keyDown(VK_RIGHT)) && Dn ) {
			if (pointer != input.resourcepacks.size()) {
				++pointer;
			}
			else {
				pointer = 0;
			}
			redraw = true;
			Dn = false;
		}
		if (keyDown(VK_RETURN)) {
			cls();
			change(input, pointer - 1);
			return true;
		}
		if (keyDown(VK_BACK) || keyDown(VK_ESCAPE)) {
			gotoxy(0, 0);
			return false;
		}
		if (keyDown(VK_SPACE) && SPACE) {
			cmd("start .\\RPManager\\resourcepacks");
			SPACE = false;
		}
		if (keyDown(VK_F5)) {
			Sleep(100);
			return true;
		}
	}
}
