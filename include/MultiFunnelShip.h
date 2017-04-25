
#ifndef _MULTIFUNNELSHIP_H
#define _MULTIFUNNELSHIP_H

#include "Ship.h"

class MultiFunnelShip: public Ship 
{
public: 
	MultiFunnelShip(Grid* myGrid, Grid* opponentsGrid, vector<Coordinates> coordinates);
    
    int getSize();
	bool canFire();
    void fire(unsigned int row, unsigned int column);
};

#endif //_MULTIFUNNELSHIP_H