#include "GameLogic.h"
#include "RandomStrategy.h"
#include "GreedyStrategy.h"
#include "GreedyStrategy.h"
#include "ConsoleDisplaying.h"
#include "ConsoleInput.h"
#include <iostream>
#include <time.h>
#include <regex>
using namespace std;

bool checkifnumber(string a);

int main(int argc, char* argv[])
{	
	srand(time(NULL));
	if (argc != 3 && argc != 4)
	{
		cout << "wrong number of arguments"<<endl;
		return 1;
	}

	string argument1(argv[1]), argument2(argv[2]);
	
	if (!checkifnumber(argument1))
	{
		cout << "first argument is not a number" << endl;
		return 1;
	}
	if (argument2 != "greedy"&&argument2!="random")
	{
		cout << "wrong name of strategy" << endl;
		return 1;
	}

	ConsoleInput* consoleinput = new ConsoleInput;
	ConsoleDisplaying* consoledisplaying = new ConsoleDisplaying;
	ChoiceStrategy* chosen;
	if (argument2 == "greedy")
	{
		chosen= new GreedyStrategy;
	}
	else if(argument2 == "random")
	{
		chosen = new RandomStrategy;
	}
	else
	{
		cout << "wrong name of strategy" << endl;
		delete consoleinput;
		delete consoledisplaying;
		return 1;
	}

	if (argc == 3)
	{

		try
		{
			GameLogic game(stoi(argument1), consoledisplaying, chosen, consoleinput);
			game.arrangeShips();
			while (!game.isGameFinished())
				game.playRound();
		}
		catch (GameLogic::WrongNumberOfRoundsException)
		{
			cout << "wrong number of rounds" << endl;
			delete consoleinput;
			delete consoledisplaying;
			delete chosen;
			return 1;
		}

	}
	else if (argc == 4)
	{
		ChoiceStrategy*chosen2;
		string argument3(argv[3]);
		if (argument3 == "greedy")
		{
			chosen2 = new GreedyStrategy;
		}
		else if (argument3 == "random")
		{
			chosen2 = new RandomStrategy;
		}
		else
		{
			cout << "wrong name of the second strategy" << endl;
			delete consoleinput;
			delete consoledisplaying;
			delete chosen;
			return 1;
		}

		try
		{
			GameLogic game(stoi(argument1), consoledisplaying, chosen, chosen2);
			game.arrangeShips();
			while (!game.isGameFinished())
				game.playRound();
		}
		catch (GameLogic::WrongNumberOfRoundsException)
		{
			cout << "wrong number of rounds" << endl;
			delete consoleinput;
			delete consoledisplaying;
			delete chosen;
			delete chosen2;
			return 1;
		}
		delete chosen2;
	}

	delete chosen;
	delete consoleinput;
	delete consoledisplaying;
}

bool checkifnumber(string a)
{
	regex pat("[\\d]+");
	if (regex_match(a, pat))
	{
		return true;
	}
	else
		return false;
}