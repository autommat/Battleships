
#ifndef _CHOICESTRATEGY_H
#define _CHOICESTRATEGY_H
#include <vector>
using namespace std;
class Ship;

class ChoiceStrategy
{
public:
	ChoiceStrategy();
	virtual ~ChoiceStrategy();
	virtual int chooseShip(vector<Ship*>) = 0;
	class NoShipCanBeChosenException {};
};

#endif //_CHOICESTRATEGY_H