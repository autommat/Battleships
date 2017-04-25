#include <boost/test/unit_test.hpp>
#include"Grid.h"
#include"OneFunnelShip.h"
#include "MultiFunnelShip.h"
#include <iostream>
#include "ConsoleInput.h"
#include "Human.h"
#include "Computer.h"
#include "RandomStrategy.h"
#include <time.h>
#include "ConsoleDisplaying.h"
#include "GameLogic.h"
#include "GreedyStrategy.h"
BOOST_AUTO_TEST_SUITE(Battleships)
BOOST_AUTO_TEST_CASE(GridFieldTest)
{
	GridField alone;
	BOOST_CHECK_EQUAL(alone.notShotYet, true);
	BOOST_CHECK_EQUAL(alone.missedShot, false);
	BOOST_CHECK_EQUAL(alone.shotShip, false);
	BOOST_CHECK_EQUAL(alone.shipHere, false);
}
BOOST_AUTO_TEST_CASE(GridFieldModificationTest)
{
	GridField alone;
	BOOST_CHECK_EQUAL(alone.notShotYet, true);
	BOOST_CHECK_EQUAL(alone.missedShot, false);
	BOOST_CHECK_EQUAL(alone.shotShip, false);
	BOOST_CHECK_EQUAL(alone.shipHere, false);
	alone.notShotYet = false;
	alone.missedShot = true;
	alone.shotShip = true;
	alone.shipHere = true;
	BOOST_CHECK_EQUAL(alone.notShotYet, false);
	BOOST_CHECK_EQUAL(alone.missedShot, true);
	BOOST_CHECK_EQUAL(alone.shotShip, true);
	BOOST_CHECK_EQUAL(alone.shipHere, true);
}
BOOST_AUTO_TEST_CASE(GridTest)
{
	Grid g;
	BOOST_CHECK_EQUAL(g.canPlaceShipHere(1,1), true);
	BOOST_CHECK_EQUAL(g.isSunkHere(1,1), false);
	BOOST_CHECK_EQUAL(g.isNotShotYetHere(1,1), true);
}


BOOST_AUTO_TEST_CASE(OneFunnelShipAllocationTest)
{
	Grid mine;
	Grid opponents;
	Coordinates c(1, 1);
	vector<Coordinates> wekt;
	wekt.push_back(c);
	OneFunnelShip s(&mine, &opponents, wekt);
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(1, 1), false);
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(1, 2), false);
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(2, 1), false);
	BOOST_CHECK_EQUAL(opponents.canPlaceShipHere(1, 1), true);
}
BOOST_AUTO_TEST_CASE(TwoFunnelShipAllocationTest)
{
	Grid mine;
	Grid opponents;
	Coordinates a(1, 1);
	Coordinates b(1, 2);
	vector<Coordinates> wekt;
	wekt.push_back(a);
	wekt.push_back(b);
	try
	{
		MultiFunnelShip s(&mine, &opponents, wekt);
	}
	catch(Ship::WrongSetOfCoordinatesException)
	{
		cout << 1;
	}
	catch (Ship::WrongSingleCoordinateException)
	{
		cout << 2;
	}
	catch (Ship::WrongSizeException)
	{
		cout << 3;
	}
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(1, 1), false);
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(1, 2), false);
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(1, 3), false);
	//BOOST_CHECK_EQUAL(mine.shipHere(1, 3), true);
	BOOST_CHECK_EQUAL(opponents.canPlaceShipHere(1, 1), true);
}
BOOST_AUTO_TEST_CASE(ThreeFunnelShipAllocationTest)
{
	Grid mine;
	Grid opponents;
	Coordinates a(1, 1);
	Coordinates b(1, 2);
	Coordinates c(1, 3);
	vector<Coordinates> wekt;
	wekt.push_back(a);
	wekt.push_back(b);
	wekt.push_back(c);
	MultiFunnelShip s(&mine, &opponents, wekt);
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(1, 1), false);
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(1, 2), false);
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(1, 3), false);
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(2, 1), false);
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(2, 2), false);
	BOOST_CHECK_EQUAL(opponents.canPlaceShipHere(1, 1), true);
}

BOOST_AUTO_TEST_CASE(ThreeFunnelShipAllocationTest2)
{
	Grid mine;
	Grid opponents;
	Coordinates a(1, 1);
	Coordinates b(1, 2);
	Coordinates c(1, 3);
	vector<Coordinates> wekt;
	wekt.push_back(a);
	wekt.push_back(b);
	wekt.push_back(c);
	try {
		MultiFunnelShip s(&mine, &opponents, wekt);
	}
	catch (Ship::WrongSetOfCoordinatesException)
	{
		cout << "set";
	}
	catch (Ship::WrongSingleCoordinateException)
	{
		cout << "single";
	}
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(1, 1), false);
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(1, 2), false);
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(1, 3), false);
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(2, 1), false);
	BOOST_CHECK_EQUAL(mine.canPlaceShipHere(2, 2), false);
	BOOST_CHECK_EQUAL(opponents.canPlaceShipHere(1, 1), true);
}
/*
BOOST_AUTO_TEST_CASE(ComputerShipAllocationTest)
{
	srand(time(NULL));
	Grid p1, p2;
	RandomStrategy strategy;
	Computer comp(&p1,&p2,&strategy);
	comp.arrangeAShip(1);
	ConsoleDisplaying console;
	comp.arrangeAShip(2);
	comp.arrangeAShip(3);
}
BOOST_AUTO_TEST_CASE(HumanShipAllocationTest)
{
	srand(time(NULL));
	Grid p1, p2;
	ConsoleInput strategy;
	Human comp(&p1,&p2,&strategy);
	comp.arrangeAShip(1);
	ConsoleDisplaying console;
	console.displayPlayer1Grids(&p1, &p2);
	comp.arrangeAShip(2);
	comp.arrangeAShip(3);
	console.displayBothPlayersGrids(&p1, &p2);
}
BOOST_AUTO_TEST_CASE(HumanUserInterfaceTest)
{
	Grid p1, p2;
	ConsoleInput con;
	Human human(&p1, &p2, &con);
	human.arrangeAShip(1);
	BOOST_CHECK_EQUAL(p1.canPlaceShipHere(1, 1), false);
}
BOOST_AUTO_TEST_CASE(ComputerShipThreeFunnelAllocationTest)
{
	srand(time(NULL));
	Grid p1, p2;
	RandomStrategy strategy;
	Computer comp(&p1, &p2, &strategy);
	comp.arrangeAShip(1);
	comp.arrangeAShip(2);
	comp.arrangeAShip(3);
	ConsoleDisplaying console;
	console.displayPlayer1Grids(&p1, &p2);
}

BOOST_AUTO_TEST_CASE(compPlayTurn)
{
	srand(time(NULL));
	GreedyStrategy strategy;
	GreedyStrategy strategy2;

	Grid p1, p2;
	ConsoleInput con;
	Computer c1(&p1, &p2,&strategy);
	Computer c2(&p2, &p1, &strategy2);
	c1.arrangeAShip(1);
	c1.arrangeAShip(2);
	c1.arrangeAShip(3);
	c2.arrangeAShip(1);
	c2.arrangeAShip(2);
	c2.arrangeAShip(3);
	ConsoleDisplaying console;
	console.displayBothPlayersGrids(&p1, &p2);
	c1.playTurn();
	c2.playTurn();
	console.displayBothPlayersGrids(&p1, &p2);
}
*/
/*
BOOST_AUTO_TEST_CASE(canFireHereTest)
{
	Grid p1, p2;
	Coordinates c1(5, 5);
	Coordinates c2(5, 6);
	vector<Coordinates> shipcoords;
	shipcoords.push_back(c1);
	shipcoords.push_back(c2);
	MultiFunnelShip m(&p1, &p2, shipcoords);
	vector<Coordinates>::iterator it;
	it = shipcoords.begin();
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (p1.canFireHere(x, y,2,it)) cout << "+";
			else cout << "-";
		}
		cout << endl;
	}
	cout << endl << endl;
}
*/
BOOST_AUTO_TEST_SUITE_END()
