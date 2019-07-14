#include "Utilities.h"
#include <string>
#include <sstream>

int StringToInteger(std::string s) {
	int num;
	std::istringstream iss(s);
	iss >> num;

	return num;
}

void LineStandardize(std::string s) {
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
}