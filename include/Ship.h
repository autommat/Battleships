
#ifndef _SHIP_H
#define _SHIP_H

#define NOT_PAUSED 0
#define HAS_SHOT_ONCE 1
#define HAS_SHOT_TWICE 2
#define LOADING 3
#include"Grid.h"
#include <vector>
#include "Coordinates.h"

using namespace std;


class Ship
{
public:
	Ship();
	virtual ~Ship();
	virtual int getSize() = 0;
	virtual void fire(unsigned int row, unsigned int column) = 0;
	int getRange(); 
	bool canFire();
	bool checkIfSunk(); //returns true if sunk
	bool checkIfPausing(); //returns true if ship is paused
	void resetPause();
	vector<Coordinates>::iterator informAboutCoordinates();
	class WrongSetOfCoordinatesException {};
	class WrongSingleCoordinateException {};
	class WrongSizeException {};
protected: 	
	Grid* opponentsGrid;
	Grid* myGrid;
	vector<Coordinates> coordinates;
    bool sunk;
	int paused = NOT_PAUSED; //NEWLY ADDED!
	int size;
	int range;

};

#endif //_SHIP_H