
#include "OneFunnelShip.h"
#include "Coordinates.h"
OneFunnelShip::OneFunnelShip(Grid* myGrid, Grid* opponentsGrid, vector<Coordinates> coordinates)
{	
	this->myGrid = myGrid;
	this->opponentsGrid = opponentsGrid;
	if (coordinates.size() != 1)
		throw WrongSizeException();
	if (!myGrid->canPlaceShipHere(coordinates[0].getRow(),coordinates[0].getColumn()))
		throw WrongSingleCoordinateException();
	size = 1;
	range = size + 1;
	this->coordinates=coordinates;
	myGrid->addShip(coordinates);
}

OneFunnelShip::~OneFunnelShip()
{
}

int OneFunnelShip::getSize() 
{
	return 1;
}

void OneFunnelShip::fire(unsigned int row, unsigned int column)
{
	if (opponentsGrid->canFireHere(row, column, this->getSize(), this->informAboutCoordinates()))
	{
		opponentsGrid->fire(row, column);
	}
}