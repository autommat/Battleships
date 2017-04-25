
#include "RandomStrategy.h"
#include "Ship.h"
#include<time.h>
#include <cstdlib>
#define NUMBER_OF_SHIPS 3

int RandomStrategy::chooseShip(vector<Ship*> ships)
{
	srand(time(NULL));
	vector<int>can_be_chosen;
	for (int i = 0; i < ships.size();i++)
		if ((ships[i])->canFire() && (!(ships[i])->checkIfPausing()))
			can_be_chosen.push_back(i);
	if (can_be_chosen.size() == 0)
		throw NoShipCanBeChosenException();
	return( can_be_chosen[rand() % can_be_chosen.size()] );
}