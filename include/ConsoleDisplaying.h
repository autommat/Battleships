
#ifndef _CONSOLEDISPLAYING_H
#define _CONSOLEDISPLAYING_H

#include "GameLogicUserInterface.h"
#include <iostream>
#include <cstdlib>

using namespace std;

class ConsoleDisplaying: public GameLogicUserInterface
{
public: 
	ConsoleDisplaying();
	~ConsoleDisplaying();
    void displayPlayer1Grids(Grid* p1Grid, Grid* p2Grid);

    void displayBothPlayersGrids(Grid* p1Grid, Grid* p2Grid);
    
	void displayInfo(stringstream& info);
private: 
};

#endif //_CONSOLEDISPLAYING_H