
#include "Computer.h"
#include "OneFunnelShip.h"
#include "MultiFunnelShip.h"
#include <cstdlib>
#define HORIZONTAL 0
#define VERTICAL 1
#define MAX_SHOTS 2

Computer::Computer(Grid * myGrid, Grid * opponentsGrid, ChoiceStrategy * choiceStrategy)
{
	this->myGrid = myGrid;
	this->opponentsGrid = opponentsGrid;
	this->choiceStrategy = choiceStrategy;
}
Computer::~Computer()
{
	for (int i = 0; i < ships.size(); i++)
		delete ships.at(i);
}
void Computer::arrangeAShip(int size)
{
	vector<Coordinates> to_assign;
	if (size == 3)
	{
		int direction = rand() %2;
		vector<Coordinates> valid3hor;
		vector<Coordinates> valid3ver;
		for (int i = 0; i <= ROWS; i++)
			for (int j = 0; j <= COLUMNS; j++)
			{
				if (direction == HORIZONTAL)
				{
					if ((*myGrid).canPlaceShipHere(i, j) && (*myGrid).canPlaceShipHere(i + 1, j) && (*myGrid).canPlaceShipHere(i - 1, j))
					{
						Coordinates c(i, j);
						Coordinates cplus1(i + 1, j);
						Coordinates cminus1(i - 1, j);
						if(cplus1.getRow()<=9 && cminus1.getRow()>=0)
						valid3hor.push_back(c);
					}
				}
				else if (direction == VERTICAL)
				{
					if ((*myGrid).canPlaceShipHere(i, j) && (*myGrid).canPlaceShipHere(i, j + 1) && (*myGrid).canPlaceShipHere(i, j - 1))
					{
						Coordinates c(i, j);
						Coordinates cplus1(i, j +1);
						Coordinates cminus1(i, j - 1);
						if(cplus1.getColumn()<=9 && cminus1.getColumn()>=0)
						valid3ver.push_back(c);
					}

				}
			}
	
		if (direction == HORIZONTAL)
		{
			Coordinates threefunnel = valid3hor.at(rand() % (valid3hor.size()));
			Coordinates threefunnelleft(threefunnel.getRow() - 1, threefunnel.getColumn());
			Coordinates threefunnelright(threefunnel.getRow() + 1, threefunnel.getColumn());
			vector<Coordinates> to_assign_hor;
			to_assign_hor.push_back(threefunnelleft);
			to_assign_hor.push_back(threefunnel);
			to_assign_hor.push_back(threefunnelright);
			ships.push_back(new MultiFunnelShip(myGrid, opponentsGrid, to_assign_hor));
		}
		else if (direction == VERTICAL)
		{
			Coordinates threefunnel = valid3ver.at(rand() % (valid3ver.size()));
			Coordinates threefunneltop(threefunnel.getRow(), threefunnel.getColumn() - 1);
			Coordinates threefunnelbottom(threefunnel.getRow(), threefunnel.getColumn() + 1);
			vector<Coordinates> to_assign_ver;
			to_assign_ver.push_back(threefunneltop);
			to_assign_ver.push_back(threefunnel);
			to_assign_ver.push_back(threefunnelbottom);
			ships.push_back(new MultiFunnelShip(myGrid, opponentsGrid, to_assign_ver));

		}
	}
	vector<Coordinates> valid1; //vector storing valid values for the first coordinate pair
	for (unsigned int i = 0; i <= ROWS; i++)
		for (unsigned int j = 0; j <= COLUMNS; j++)
			if ((*myGrid).canPlaceShipHere(i, j))
			{
				Coordinates c(i, j);
				valid1.push_back(c);
			}
	Coordinates first = valid1.at(rand() % (valid1.size())); // choosing the first coordinate pair randomly from the set of valid coordinates
	to_assign.push_back(first);
	if (size == 1)
	{
		ships.push_back(new OneFunnelShip(myGrid, opponentsGrid, to_assign));
		return;
	}
	vector<Coordinates> valid2; //vector storing valid values for the second coordinate pair
								// checking the 4 - neighbourhood of the first chosen coordinate pair to find possible values of the second coordinate pair
	if ((*myGrid).canPlaceShipHere(first.getRow(), first.getColumn() + 1))
	{
		Coordinates c2(first.getRow(), first.getColumn() + 1);
		valid2.push_back(c2);
	}
	if ((*myGrid).canPlaceShipHere(first.getRow(), first.getColumn() - 1))
	{
		Coordinates c2(first.getRow(), first.getColumn() - 1);
		valid2.push_back(c2);
	}
	if ((*myGrid).canPlaceShipHere(first.getRow() + 1, first.getColumn()))
	{
		Coordinates c2(first.getRow() + 1, first.getColumn());
		valid2.push_back(c2);
	}
	if ((*myGrid).canPlaceShipHere(first.getRow() - 1, first.getColumn()))
	{
		Coordinates c2(first.getRow() - 1, first.getColumn());
		valid2.push_back(c2);
	}
	Coordinates second = valid2.at(rand() % (valid2.size())); // choosing the second pair randomly from the set of valid coordinates
	to_assign.push_back(second);
	if (size == 2)
	{
		ships.push_back(new MultiFunnelShip(myGrid, opponentsGrid, to_assign));
		return;
	}
	return;
}
void Computer::playTurn() 
{
	int chosenShipindex;
	vector<Coordinates> validShootingCoords;
	try
	{
		chosenShipindex = choiceStrategy->chooseShip(ships);
	}
	catch (ChoiceStrategy::NoShipCanBeChosenException)
	{
		return;
	}

		for (int k = 0; k < MAX_SHOTS; ++k)
		{
			for (unsigned int i = 0; i < ROWS; i++)
				for (unsigned int j = 0; j < COLUMNS; j++)
				{
					if ((*opponentsGrid).canFireHere(i, j, (ships.at(chosenShipindex)->getSize()), ships[chosenShipindex]->informAboutCoordinates()))
					{
						Coordinates c(i, j);
						validShootingCoords.push_back(c);
					}
					else continue;
				}
			if (validShootingCoords.size() != 0)
			{
				Coordinates shootHere = validShootingCoords.at(rand() % validShootingCoords.size());
				ships.at(chosenShipindex)->fire(shootHere.getRow(), shootHere.getColumn());
			}
			if (chosenShipindex == 0) return;
		}
    return;
}