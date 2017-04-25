/**
 * Project Untitled
 */


#ifndef _COMPUTER_H
#define _COMPUTER_H

#include "Player.h"
#include "ChoiceStrategy.h"


class Computer: public Player
{
public: 
	Computer(Grid* myGrid, Grid* opponentsGrid, ChoiceStrategy* choiceStrategy);
	virtual ~Computer();
    
    void arrangeAShip(int size);
    
    void playTurn();
private: 
    ChoiceStrategy* choiceStrategy;
};

#endif //_COMPUTER_H