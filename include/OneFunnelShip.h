
#ifndef _ONEFUNNELSHIP_H
#define _ONEFUNNELSHIP_H

#include "Ship.h"
class Coordinates;

class OneFunnelShip: public Ship 
{
public:
    OneFunnelShip(Grid* myGrid, Grid* opponentsGrid, vector<Coordinates> coordinates);
	~OneFunnelShip();
    int getSize();
    void fire(unsigned int row,unsigned int column);
};

#endif //_ONEFUNNELSHIP_H