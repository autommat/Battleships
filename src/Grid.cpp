
#include "Grid.h"
#include <cmath>
#include "Coordinates.h"

void Grid::addShip(vector<Coordinates>to_add) 
{
	bool can_be_added = true;
	for (int i = 0;i < to_add.size();i++)
	{
		if (!canPlaceShipHere(to_add[i].getRow(), to_add[i].getColumn()))
			can_be_added = false;
	}
	if (can_be_added)
	{
		for(int i=0;i< to_add.size();i++)
			fields[to_add[i].getRow()][to_add[i].getColumn()].shipHere = true;
	}
}

bool Grid::canPlaceShipHere(unsigned int row, unsigned int column) //has to be called for each pair of coordinates that are to be assigned to a ship
{
	if (row >= ROWS || column >= COLUMNS)
	{
		return false;
	}

	for (signed int i = static_cast<signed int>(row) - 1;i < static_cast<signed int>(row) + 2;i++)
	{
		for (signed int j = static_cast<signed int>(column) - 1;j < static_cast<signed int>(column) + 2;j++)
		{
			if ((i < 0) || (i >= ROWS) || (j < 0) || (j >= COLUMNS))
				continue;
			else if (fields[i][j].shipHere)
				return false;
		}
	}
	return true;
}

bool Grid::canFireHere(unsigned int row, unsigned int column, int size, vector<Coordinates>::iterator coordinates)
{
	if (row >= ROWS || column >= COLUMNS)
		throw OutOfGridRangeException();

	if (!fields[row][column].notShotYet)
		return false;

	int ship_range = size + 1;
	for (int i = 0; i < size; i++, coordinates++)
	{
		if (abs((int)(row - coordinates->getRow())) <= ship_range)
			if (abs((int)(column - coordinates->getColumn())) <= ship_range)
				return true;
	}
	return false;
}

void Grid::fire(unsigned int row, unsigned int column)
{
	if (row >= ROWS || column >= COLUMNS)
		throw OutOfGridRangeException();

	fields[row][column].notShotYet = false;
	if (fields[row][column].shipHere)
	{
		fields[row][column].shotShip = true;
	}
	else
	{
		fields[row][column].missedShot = true;
	}
}

bool Grid::isSunkHere(unsigned int row, unsigned int column) 
{
	if (row >= ROWS || column >= COLUMNS)
		throw OutOfGridRangeException();
	else
		return fields[row][column].shotShip;
}

bool Grid::isNotShotYetHere(unsigned int row, unsigned int column) 
{
	if (row >= ROWS || column >= COLUMNS)
		throw OutOfGridRangeException();
	else
		return fields[row][column].notShotYet;
}

bool Grid::isShipHere(unsigned int row, unsigned int column) 
{
	if (row >= ROWS || column >= COLUMNS)
		throw OutOfGridRangeException();
	else
		return fields[row][column].shipHere;
}