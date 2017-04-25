
#include "ConsoleDisplaying.h"
#include "Grid.h"
#include <iostream>

using namespace std;

ConsoleDisplaying::ConsoleDisplaying()
{
}

ConsoleDisplaying::~ConsoleDisplaying()
{
}

void ConsoleDisplaying::displayPlayer1Grids(Grid* p1Grid, Grid* p2Grid)
{
	system("pause");
	cout << "Legend: |*| - location where your ship is placed \t |O| - location where a ship is sunk \t |x| - location that was already shot by you \t |-| - location that was already shot by your opponent" << endl;
	cout << "Your Grid:" << endl;
	cout << "   |0|1|2|3|4|5|6|7|8|9| COLUMNS" << endl;
	for (int i = 0; i < ROWS; i++)
	{
		cout << "|" << i << "|";
		for (int j = 0; j < COLUMNS; j++)
		{
			cout << "|";
			if (p1Grid->isShipHere(i, j))
			{
				if (p1Grid->isSunkHere(i, j))
					cout << "O";
				else
					cout << "*";
			}
			else if (!(p1Grid->isNotShotYetHere(i, j))) cout << "-";
			else cout << " ";
		}
		cout << "|";
		cout << endl;
	}
	cout << "ROWS" << endl;
	cout << endl;
	cout << "Opponent's Grid:" << endl;
	cout << "   |0|1|2|3|4|5|6|7|8|9| COLUMNS" << endl;
	for (int i = 0; i < ROWS; i++)
	{
		cout << "|" << i << "|";
		for (int j = 0; j < COLUMNS; j++)
		{
			cout << "|";
			if (!(p2Grid->isNotShotYetHere(i, j)))
			{
				if (p2Grid->isSunkHere(i, j))
					cout << "O";
				else
					cout << "x";
			}
			else cout << " ";
		}
		cout << "|";
		cout << endl;
	}
	cout << "ROWS" << endl;
	cout << endl;
}

void ConsoleDisplaying::displayBothPlayersGrids(Grid* p1Grid, Grid* p2Grid)
{
	system("pause");
	cout << "Legend: |*| - location where your ship is placed \t |O| - location where a ship is sunk \t |x| - location that was already shot by you \t |-| - location that was already shot by your opponent"   << endl;
	cout << "Player 1 Grids: " << endl << endl;
	cout << "Primary Grid" << endl;
	cout << "   |0|1|2|3|4|5|6|7|8|9| COLUMNS" << endl;
	for (int i = 0; i < ROWS; i++)
	{
		cout << "|" << i << "|";
		for (int j = 0; j < COLUMNS; j++)
		{
			cout << "|";
			if (p1Grid->isShipHere(i, j))
			{
				if (p1Grid->isSunkHere(i, j))
					cout << "O";
				else
					cout << "*";
			}
			else if (!(p1Grid->isNotShotYetHere(i, j))) cout << "-";
			else cout << " ";
		}
		cout << "|";
		cout << endl;
	}
	cout << "ROWS" << endl;
	cout << endl;
	cout << "Secondary Grid" << endl;
	cout << "   |0|1|2|3|4|5|6|7|8|9| COLUMNS" << endl;
	for (int i = 0; i < ROWS; i++)
	{
		cout << "|" << i << "|";
		for (int j = 0; j < COLUMNS; j++)
		{
			cout << "|";
			if (!(p2Grid->isNotShotYetHere(i, j)))
			{
				if (p2Grid->isSunkHere(i, j))
					cout << "O";
				else
					cout << "x";
			}
			else cout << " ";
		}
		cout << "|";
		cout << endl;
	}
	cout << "ROWS" << endl;
	cout << endl;
	cout << "Player 2 Grids: " << endl << endl;
	cout << "Primary Grid" << endl;
	cout << "   |0|1|2|3|4|5|6|7|8|9| COLUMNS" << endl;
	for (int i = 0; i < ROWS; i++)
	{
		cout << "|" << i << "|";
		for (int j = 0; j < COLUMNS; j++)
		{
			cout << "|";
			if (p2Grid->isShipHere(i, j))
			{
				if (p2Grid->isSunkHere(i, j))
					cout << "O";
				else
					cout << "*";
			}
			else if (!(p2Grid->isNotShotYetHere(i, j))) cout << "-";
			else cout << " ";
		}
		cout << "|";
		cout << endl;
	}
	cout << "ROWS" << endl;
	cout << endl;
	cout << "Secondary Grid" << endl;
	cout << "   |0|1|2|3|4|5|6|7|8|9| COLUMNS" << endl;
	for (int i = 0; i < ROWS; i++)
	{
		cout << "|" << i << "|";
		for (int j = 0; j < COLUMNS; j++)
		{
			cout << "|";
			if (!(p1Grid->isNotShotYetHere(i, j)))
			{
				if (p1Grid->isSunkHere(i, j))
					cout << "O";
				else
					cout << "x";
			}
			else cout << " ";
		}
		cout << "|";
		cout << endl;
	}
	cout << "ROWS" << endl;
}

void ConsoleDisplaying::displayInfo(stringstream& info)
{
	cout << info.str() << endl;
	info.str(string(""));//emptying stream
}
