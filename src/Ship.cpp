
#include "Ship.h"
#include "GridField.h"

int Ship::getRange()
{
	return range;
}

bool Ship::canFire()
{
	if (this->checkIfSunk())
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

bool Ship::checkIfSunk() 
{
	for (int i = 0; i < size; i++)
	{
		if (!myGrid->isSunkHere(coordinates[i].getRow(), coordinates[i].getColumn()))
			return false;
	}
	return true;
}

bool Ship::checkIfPausing()
{
	if (paused == NOT_PAUSED||paused==HAS_SHOT_ONCE)
		return false;
	else
		return true;
}

void Ship::resetPause()
{
	if (paused == HAS_SHOT_ONCE || paused == LOADING)
		paused = NOT_PAUSED;
	else if (paused == HAS_SHOT_TWICE)
		paused = LOADING;

}

vector<Coordinates>::iterator Ship::informAboutCoordinates()
{
	vector<Coordinates>::iterator it;
	it = coordinates.begin();
	return it;
}

Ship::Ship()
{
}

Ship::~Ship()
{
}
