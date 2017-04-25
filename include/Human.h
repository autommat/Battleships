
#ifndef _HUMAN_H
#define _HUMAN_H

#include "Player.h"
#include "HumanUserInterface.h"


class Human: public Player 
{
public: 
    Human(Grid* myGrid, Grid* opponentsGrid, HumanUserInterface* user);
	~Human();
    void arrangeAShip(int size);
    void playTurn();
private: 
	HumanUserInterface* UI;
};

#endif //_HUMAN_H