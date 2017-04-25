
#ifndef _GAMELOGICUSERINTERFACE_H
#define _GAMELOGICUSERINTERFACE_H
#include <sstream>
using namespace std;

class Grid;

class GameLogicUserInterface 
{
public: 
	virtual ~GameLogicUserInterface();

    virtual void displayPlayer1Grids(Grid* p1Grid, Grid* p2Grid) = 0;

    virtual void displayBothPlayersGrids(Grid* p1Grid, Grid* p2Grid) = 0;
    
    virtual void displayInfo(stringstream& info) = 0;
};

#endif //_GAMELOGICUSERINTERFACE_H