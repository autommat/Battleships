#include "MultiFunnelShip.h"
#include <cmath>

MultiFunnelShip::MultiFunnelShip(Grid* myGrid, Grid* opponentsGrid, vector<Coordinates> coordinates)
{
	this->myGrid = myGrid;
	this->opponentsGrid = opponentsGrid;
	if (coordinates.size()!=2 && coordinates.size() != 3)
		throw WrongSizeException();

	for (int i = 0;i < coordinates.size();i++)
	{
		if (!myGrid->canPlaceShipHere(coordinates[i].getRow(), coordinates[i].getColumn()))
			throw WrongSingleCoordinateException();
	}

	bool vertical = true;
	bool horizontal = true;
	for (int i = 0;i < coordinates.size() - 1;i++)
	{
		if (abs(static_cast<int>(coordinates[i].getRow() - coordinates[i + 1].getRow())) > 1 || //checking if subsequent horizontal coordinates are adjacent or the same
			abs(static_cast<int>(coordinates[i].getColumn() - coordinates[i + 1].getColumn())) > 1 || //checking if subsequent vertical coordinates are adjacent or the same
			(coordinates[i].getRow()==coordinates[i+1].getRow()&&coordinates[i].getColumn()==coordinates[i+1].getColumn()) ) //checking if subsequent coordinates are the same
		{
			throw WrongSetOfCoordinatesException();
		}
		if (coordinates[i].getRow() != coordinates[i + 1].getRow())
		{
			horizontal = false;
		}
		if (coordinates[i].getColumn() != coordinates[i + 1].getColumn())
		{
			vertical = false;
		}
	}
	if(!horizontal && !vertical) 
		throw WrongSetOfCoordinatesException();

	this->coordinates = coordinates;
	this->size = coordinates.size();
	this->range = size + 1;
	myGrid->addShip(coordinates);
}

int MultiFunnelShip::getSize() 
{
	return size;
}

bool MultiFunnelShip::canFire()
{
	if (this->checkIfSunk() || paused >= HAS_SHOT_TWICE)
		return false;
	else
	{
		for (int i = 0;i < size;i++)
		{
			for (signed int x = static_cast<signed int>(coordinates[i].getRow()) - range; x <= static_cast<signed int>(coordinates[i].getRow()) + range; x++)
			{
				for (signed int y = static_cast<signed int>(coordinates[i].getColumn()) - range;y <= static_cast<signed int>(coordinates[i].getColumn()) + range;y++)
				{
					if (x < 0 || y < 0 || x >= ROWS || y >= COLUMNS)
						continue;
					if (opponentsGrid->isNotShotYetHere(x, y))
					{
						return true; //because there is a field where one of ships can fire
					}
				}
			}
		}
		return false;
	}
}

void MultiFunnelShip::fire(unsigned int row, unsigned int column)
{
	if (opponentsGrid->canFireHere(row, column, this->getSize(), this->informAboutCoordinates())
		&& this->canFire()	)
	{
		opponentsGrid->fire(row, column);
		paused++;
	}
}

