
#include "ConsoleInput.h"
#include<iostream>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

ConsoleInput::ConsoleInput()
{
}

int ConsoleInput::getCoordinate()
{
	string input;
	int coord;
	do
	{
		cin >> coord;

		if (!cin || coord < SMALLEST_NUMBER_USED_IN_PROGRAM || coord>BIGGEST_NUMBER_USED_IN_PROGRAM)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "wrong input! try again:";
		}
	} while (!cin || coord < SMALLEST_NUMBER_USED_IN_PROGRAM || coord>BIGGEST_NUMBER_USED_IN_PROGRAM);
	return coord;
}

void ConsoleInput::displayInfo(stringstream& info)
{
	cout << info.str() << endl;
	info.str(string(""));//emptying stream
}

void ConsoleInput::operator<<(stringstream& str)
{
	displayInfo(str);
}


