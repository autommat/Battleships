
#include "GreedyStrategy.h"
#include "Ship.h"
using namespace std;
int GreedyStrategy::chooseShip(vector<Ship*> ships)
{
	if ((ships[2])->canFire() && (!((ships[2])->checkIfPausing())))
	{	
		return 2;
	}
	else if ((ships[1])->canFire() && ((!(ships[1])->checkIfPausing())))
	{
		return 1;
	}
	else if (((ships[0])->canFire()) && ((!(ships[0])->checkIfPausing())))
	{
		return 0;
	}
	else
		throw ChoiceStrategy::NoShipCanBeChosenException();
}