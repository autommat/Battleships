
#ifndef _GAMELOGIC_H
#define _GAMELOGIC_H

#define COMPUTER_AND_HUMAN_MODE 1
#define TWO_COMPUTERS_MODE 2
#include "Grid.h"
#include "Player.h"
#include "Grid.h"
#include <string>
#include "GameLogicUserInterface.h"
#include "HumanUserInterface.h"
#include "ChoiceStrategy.h"

using namespace std;

class GameLogic 
{
public: 
	int currentRoundNumber=1;
	GameLogic(int rounds, GameLogicUserInterface* UI, ChoiceStrategy* strategy1, ChoiceStrategy* strategy2);
	GameLogic(int rounds, GameLogicUserInterface* UI, ChoiceStrategy* strategy1, HumanUserInterface* humanUI);
	~GameLogic();
    void arrangeShips();
    void playRound();   
	bool isGameFinished();
	class WrongNumberOfRoundsException{};
private: 	
	const int mode;
    const int maxRoundsNumber;
    Grid* player1Grid;
    Grid* player2Grid;	
	GameLogicUserInterface* display; 
	Player* player1;
	Player* player2;


};

#endif //_GAMELOGIC_H