#pragma once
#ifndef _console_header
#define _console_header

#define colorGreen   10
#define colorCyan   11
#define colorYellow   14
#define colorDefault   7
#define colorWhite 15
#define colorRed 12

#define keyUp			1072
#define keyDown			1080
#define keyLeft			1075
#define keyRight		1077
#define keyNone			-1

#include <windows.h>

void SetCursorVisible(bool isVisible);
int InputKey();
void Clrscr();
void ClrLine(int line);
void GotoXY(int column, int line);
int WhereX();
int WhereY();
void SetColor(int color);


#endif