
#include "GameLogic.h"
#include "Computer.h"
#include "Human.h"
#include "GreedyStrategy.h"
#include "RandomStrategy.h"
#include "ConsoleInput.h"
#include "ConsoleDisplaying.h"

GameLogic::GameLogic(int rounds, GameLogicUserInterface* UI, ChoiceStrategy* strategy1, ChoiceStrategy* strategy2) : maxRoundsNumber(rounds), mode(TWO_COMPUTERS_MODE)
{
	if (maxRoundsNumber <= 1 || maxRoundsNumber > 20)
		throw WrongNumberOfRoundsException();
	player1Grid = new Grid;
	player2Grid = new Grid;

	display = UI;
	player1 = new Computer(player1Grid, player2Grid, strategy1);
	player2 = new Computer(player2Grid, player1Grid, strategy2);
}

GameLogic::GameLogic(int rounds, GameLogicUserInterface* UI, ChoiceStrategy* strategy1, HumanUserInterface* humanUI) : maxRoundsNumber(rounds), mode(COMPUTER_AND_HUMAN_MODE)
{
	if (maxRoundsNumber <= 1 || maxRoundsNumber > 20)
		throw WrongNumberOfRoundsException();
	player1Grid = new Grid;
	player2Grid = new Grid;

	display = UI;
	player1 = new Human(player1Grid, player2Grid, humanUI);
	player2 = new Computer(player2Grid, player1Grid, strategy1);
}

GameLogic::~GameLogic()
{
	delete player1Grid;
	delete player2Grid;
	delete player1;
	delete player2;
}

void GameLogic::arrangeShips() 
{
	for (int i = 1;i <= NUMBER_OF_SHIPS;i++)
	{
		if (mode == COMPUTER_AND_HUMAN_MODE)
			display->displayPlayer1Grids(player1Grid, player2Grid); 
		else
			display->displayBothPlayersGrids(player1Grid, player2Grid);

		player1->arrangeAShip(i);

		if (mode == COMPUTER_AND_HUMAN_MODE)
			display->displayPlayer1Grids(player1Grid, player2Grid);
		else
			display->displayBothPlayersGrids(player1Grid, player2Grid);
		
		player2->arrangeAShip(i);
	}
	if (mode == COMPUTER_AND_HUMAN_MODE)
		display->displayPlayer1Grids(player1Grid, player2Grid);
	else
		display->displayBothPlayersGrids(player1Grid, player2Grid);

	stringstream info;
	info << "Arranging ships finished";
	display->displayInfo(info);
}

void GameLogic::playRound() 
{
	stringstream info;
	info << "round number " << currentRoundNumber<<" of "<<maxRoundsNumber;
	display->displayInfo(info);
	player1->playTurn();
	player2->playTurn();
	player1->resetShips();
	player2->resetShips();
	if (mode == COMPUTER_AND_HUMAN_MODE)
		display->displayPlayer1Grids(player1Grid, player2Grid);
	else
		display->displayBothPlayersGrids(player1Grid, player2Grid);
	currentRoundNumber++;
    return;
}

bool GameLogic::isGameFinished()
{
	if (!player1->canKeepPlaying() || !player2->canKeepPlaying() || currentRoundNumber >= maxRoundsNumber)
	{
		stringstream info;
		info << "Game Over. ";
		if (!player1->canKeepPlaying())
		{
			info << "player 2 has won!";
			display->displayInfo(info);
			return true;
		}
		if (!player2->canKeepPlaying())
		{
			info << "player 1 has won!";
			display->displayInfo(info);
			return true;
		}
		if (currentRoundNumber >= maxRoundsNumber)
		{
			int player1shipslost = 0, player2shipslost = 0;
			for (int i = 0;i < ROWS;i++)
				for (int j = 0;j < COLUMNS;j++)
				{
					if (player1Grid->isSunkHere(i, j))
					{
						player1shipslost++;
					}
					if (player2Grid->isSunkHere(i, j))
					{
						player2shipslost++;
					}
				}
			if (player2shipslost > player1shipslost)
			{
				if (mode == COMPUTER_AND_HUMAN_MODE)
				{
					info << "You won! You shot ";
				}
				else
				{
					info << "player 1 won! He shot ";
				}

				info << player2shipslost << " fields of opponents ship and lost only " << player1shipslost;
			}

			if (player1shipslost > player2shipslost)
			{
				if (mode == COMPUTER_AND_HUMAN_MODE)
				{
					info << "You lost. The computer shot ";
				}
				else
				{
					info << "player 2 won! He shot ";
				}

				info << player1shipslost << " fields of opponents ship and lost only " << player2shipslost;
			}

			if(player1shipslost == player2shipslost)
				info << "The game finished with draw";
		}

		display->displayInfo(info);
		return true;
	}
	else
		return false;
}


