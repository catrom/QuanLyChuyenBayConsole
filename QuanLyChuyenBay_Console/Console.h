#pragma once
#ifndef _console_header
#define _console_header

#define colorHeader1   10
#define colorHeader2   11
#define colorHeader3   14
#define colorDefault   7
#define colorChoosen 15
#define colorError 12

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