
#include "Player.h"
#include "Grid.h"
#include "Coordinates.h"
bool Player::canKeepPlaying() 
{
	bool allShipsSunk = true;//I assume that all ships are sunk
	
	vector<Ship*>::iterator shipBeingChecked = ships.begin();
	for (int i = 0; i < NUMBER_OF_SHIPS; i++, shipBeingChecked++)
	{
		if (!(*shipBeingChecked)->checkIfSunk()) //if I find a ship that is not sunk, I know that "allShipsSunk" is false
		{
			allShipsSunk = false;
			break;
		}
	}

	bool noShipCanFire = true;
	for (int i = 0; i < NUMBER_OF_SHIPS; i++)
	{
		if (ships[i]->canFire())
		{
			noShipCanFire = false;
		}
	}
	return (!(allShipsSunk || noShipCanFire));
}

void Player::resetShips()
{
	for (int i = 0;i < ships.size();i++)
		ships[i]->resetPause();
}

vector<Ship*>::iterator Player::informAboutShips()
{
	vector<Ship*>::iterator it;
	it = ships.begin();
	return it;
}

Player::~Player()
{
}

