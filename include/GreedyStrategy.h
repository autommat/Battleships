
#ifndef _GREEDYSTRATEGY_H
#define _GREEDYSTRATEGY_H

#include "ChoiceStrategy.h"

class Ship;

class GreedyStrategy: public ChoiceStrategy 
{
public:
	int chooseShip(vector<Ship*> ships);
};

#endif //_GREEDYSTRATEGY_H