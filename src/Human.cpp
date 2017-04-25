#include "Human.h"
#include "Ship.h"
#include "OneFunnelShip.h"
#include "MultiFunnelShip.h"
#include <string>
#include <sstream>

using namespace std;

Human::Human(Grid * myGrid, Grid * opponentsGrid, HumanUserInterface * user)
{
	this->myGrid = myGrid;
	this->opponentsGrid = opponentsGrid;
	this->UI = user;
}

Human::~Human()
{
	for (int i = 0;i < ships.size();i++)
		delete ships[i];
}

void Human::arrangeAShip(int size) 
{
	stringstream info;
	info << "Choose " << size << " subsequent pair(s) of coordinates for the ship of size: " << size;
	*UI << info;

	bool ship_correctly_created = false;
	do
	{
		vector<Coordinates>to_assign;

		for (int coord = 0;coord < size; coord++)
		{
			unsigned int chosen_row, chosen_column;
			info << "field number " << coord + 1 << " of " << size;
			*UI << info;
			info << "row:";
			*UI << info;
			chosen_row = UI->getCoordinate();
			info << "column:";
			*UI << info;
			chosen_column = UI->getCoordinate();
			to_assign.push_back(Coordinates(chosen_row, chosen_column));
		}

		try
		{
			if (size == 1)
			{
				ships.push_back(new OneFunnelShip(myGrid, opponentsGrid, to_assign));
				ship_correctly_created = true;
			}
			else
			{
				ships.push_back(new MultiFunnelShip(myGrid, opponentsGrid, to_assign));
				ship_correctly_created = true;
			}
		}
		catch (Ship::WrongSingleCoordinateException& exception)
		{
			ship_correctly_created = false;
			info << "coordinates for one of the ship's fields were chosen incorrectly";
			*UI << info;
			info << "remember that ship must not overlap nor touch one another and given coordinates should be subsequent";
			*UI << info;
		}
		catch (Ship::WrongSetOfCoordinatesException& exception)
		{
			ship_correctly_created = false;
			info << "coordinates are not arranged properly! Remember that ship must be put horizontally or vertically.";
			*UI << info;
		}
		if (!ship_correctly_created)
		{
			info << "you must assign coordinates for ship of size " << size << " again.";
			*UI << info;
		}
	} while (!ship_correctly_created);
	info << "ship of size " << size << " successfully added!";
}

void Human::playTurn() 
{
	stringstream info;

	bool no_ship_can_fire = true, one_of_ships_is_paused=false;
	for (int i = 0;i < ships.size();i++)
	{
		if (ships[i]->canFire())
			no_ship_can_fire = false;
		if (ships[i]->checkIfPausing())
			one_of_ships_is_paused = true;
	}
	if (no_ship_can_fire&&one_of_ships_is_paused)
	{
		info << "your ships that can fire are paused. you have to skip this turn";
		*UI << info;
		return;
	}


	info << "Choose number (size) of the ship (from 1 to 3) that is going to fire.";
	*UI << info;
	info << "These ships cannot fire: ";
	for (int i = 0;i < NUMBER_OF_SHIPS;i++)
	{
		if (!ships[i]->canFire()||ships[i]->checkIfPausing())
		{
			info << (i + 1)<<" ";
		}
	}
	*UI << info;

	int ship_choice;
	bool correct_choice = false;
	do
	{ 	
		info << "ship number:";
		*UI << info;
		ship_choice=UI->getCoordinate()-1;
		try
		{
			if (!ships.at(ship_choice)->canFire()|| ships.at(ship_choice)->checkIfPausing()) 
				correct_choice = false;
			else
				correct_choice = true;
		}
		catch (out_of_range)
		{
			correct_choice = false;
		}

		if (!correct_choice)
		{
			info << "You cannot choose this ship! try again";
			*UI << info;
		}
	} while (!correct_choice);
	

	info << "Choose coordinates of the field that you want to fire at.";
	*UI << info;
	int row_choice, column_choice;
	correct_choice = false;
	do
	{
		info << "row:";
		*UI << info;
		row_choice = UI->getCoordinate();
		info << "column:";
		*UI << info;
		column_choice = UI->getCoordinate();
		try
		{
			if (opponentsGrid->canFireHere(row_choice, column_choice, ships[ship_choice]->getSize(), ships[ship_choice]->informAboutCoordinates()))
			{
				ships[ship_choice]->fire(row_choice, column_choice);
				correct_choice = true;
			}
			else
				correct_choice = false;
		}
		catch (Grid::OutOfGridRangeException)
		{
			correct_choice = false;
		}

		if (!correct_choice)
		{
			info << "You cannot fire at this field! try again";
			*UI << info;
		}
	} while (!correct_choice);

	info << "fired at: "<<row_choice<<","<<column_choice<<" and ";
	if (opponentsGrid->isSunkHere(row_choice, column_choice))
		info << "hit";
	else
		info << "missed";
	info << " opponent\'s ship";
	*UI << info;

	if (ships[ship_choice]->getSize() > 1)
	{
		info << "fire again? NO-input:0 YES-input:any other number from range [1,9]";
		*UI << info;
		int decision = UI->getCoordinate();
		if (decision != 0)
		{
			info << "Choose coordinates of the field that you want to fire at.";
			*UI << info;
			int row_choice, column_choice;
			correct_choice = false;
			do
			{
				info << "row:";
				*UI << info;
				row_choice = UI->getCoordinate();
				info << "column:";
				*UI << info;
				column_choice = UI->getCoordinate();
				try
				{
					if (opponentsGrid->canFireHere(row_choice, column_choice, ships[ship_choice]->getSize(), ships[ship_choice]->informAboutCoordinates()))
					{
						ships[ship_choice]->fire(row_choice, column_choice);
						correct_choice = true;
					}
					else
						correct_choice = false;
				}
				catch (Grid::OutOfGridRangeException)
				{
					correct_choice = false;
				}

				if (!correct_choice)
				{
					info << "You cannot fire at this field! try again";
					*UI << info;
				}
			} while (!correct_choice);
			info << "fired at: " << row_choice << "," << column_choice << " and ";
			if (opponentsGrid->isSunkHere(row_choice, column_choice))
				info << "hit";
			else
				info << "missed";
			info << " opponent\'s ship";
			*UI << info;
		}
	}
}