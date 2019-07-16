#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <Windows.h>
using namespace std;

// Console
#define colorHeader 224
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

void SetCursorVisible(bool isVisible);
int InputKey();
void Clrscr();
void ClrLine(int line);
void GotoXY(int column, int line);
int WhereX();
int WhereY();
void SetColor(int color);

// 
using namespace std;
int StringToInteger(std::string s);
std::string LineStandardize(std::string s);

// input
struct Input {
private:
	std::string result;

public:
	int GetInput();
	std::string GetResult();

	bool isInteger();
	bool isString();
};

static Input * input = new Input;