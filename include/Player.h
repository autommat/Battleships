
#ifndef _PLAYER_H
#define _PLAYER_H

#define NUMBER_OF_SHIPS 3

#include <vector>
#include "Ship.h"
using namespace std;

class Grid;

class Player 
{
public:
	virtual ~Player(); 

    virtual void arrangeAShip(int size) = 0;
    
    virtual void playTurn() = 0;
    
    bool canKeepPlaying();

	void resetShips();
    
    vector<Ship*>::iterator informAboutShips();
protected: 
	Grid* myGrid;
	Grid* opponentsGrid;

	vector<Ship*> ships;
};

#endif //_PLAYER_H