#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>

#define Maximize ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
#define Minimize ShowWindow(GetConsoleWindow(),SW_MINIMIZE);

#define Black			0
#define DarkBlue		1
#define DarkGreen		2
#define DarkCyan		3
#define Red				4
#define Violet			5
#define BrownYellow		6
#define WhiteGrey		7
#define Grey			8
#define Blue			9
#define Green			10
#define Cyan			11
#define RedPink			12
#define Magenta			13
#define WhiteYellow		14
#define White			15

void gotoxy(int x, int y) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}

void SetColor(int x) {
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, x);
}

int whereX() {
	CONSOLE_SCREEN_BUFFER_INFO x;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &x);
    return x.dwCursorPosition.X;
}

int whereY() {
	CONSOLE_SCREEN_BUFFER_INFO y;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &y);
	return y.dwCursorPosition.Y;
}

void HideCur(bool hide) {
	HANDLE x = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO y;
    y.dwSize = 10;
    y.bVisible = hide;
    SetConsoleCursorInfo(x, &y);
}


