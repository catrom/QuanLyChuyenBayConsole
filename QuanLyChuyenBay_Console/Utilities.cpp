#include "Utilities.h"

int StringToInteger(std::string s) {
	int num;
	std::istringstream iss(s);
	iss >> num;

	return num;
}

std::string LineStandardize(std::string s) {
	int n = s.size() - 1;

	while (s[0] == ' ' || s[0] == '\n')
	{
		for (int i = 0; i < n; i++)
			s[i] = s[i + 1];
		n--;
	}

	while (s[n] == ' ' || s[n] == '\n')
	{
		s[n] = '\0';
		n--;
	}

	return s;
}

void SetCursorVisible(bool isVisible)
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = isVisible;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

int InputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)	// special key
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
		return keyNone;

	return keyNone;
}

void Clrscr()
{
	SetColor(colorDefault);
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void ClrLine(int line)
{
	GotoXY(0, line);
	SetColor(colorDefault);
	printf("\r                                                                                        ");
}

void GotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int WhereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}

int WhereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int Input::GetInput()
{
	result = "";

	while (1) {
		char c = InputKey();
		if (c == 13) 
			return 1; // Enter key
		if (c == 27) 
			return -1; // ESC key
		if (c == 8) {
			result = result.substr(0, result.size() - 1);
			GotoXY(WhereX() - 1, WhereY()); cout << ' ';
		}

		if (c != keyNone) {
			if (c != 8) 
				result += char(c);			
			cout << char(c);
		}
	}
}

std::string Input::GetResult()
{
	return result;
}

bool Input::isInteger()
{
	for (int i = 0; i < result.size(); i++) {
		if (!(result[i] >= '0' && result[i] <= '9'))
			return 0;
	}

	return 1;
}

bool Input::isListOfIntegers()
{
	for (int i = 0; i < result.size(); i++) {
		if (!(result[i] >= '0' && result[i] <= '9') && result[i] != ' ')
			return 0;
	}

	return 1;
}

bool Input::isString()
{
	return result.size() > 0;
}

std::vector<int> Input::splitIntegers()
{
	std::vector<int> list;
	std::stringstream sstr(result);
	std::string segment;

	while (std::getline(sstr, segment, ' ')) {
		list.push_back(StringToInteger(segment));
	}

	return list;
}
