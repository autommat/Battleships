#ifndef _RANDOMSTRATEGY_H
#define _RANDOMSTRATEGY_H

#include "ChoiceStrategy.h"
class Ship;

class RandomStrategy: public ChoiceStrategy 
{
public: 
	int chooseShip(vector<Ship*> ships);
};

#endif //_RANDOMSTRATEGY_H