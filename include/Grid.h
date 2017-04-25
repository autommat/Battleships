#ifndef _GRID_H
#define _GRID_H

#include "GridField.h"
#include <vector>
#define ROWS 10
#define COLUMNS 10

using namespace std;
class Coordinates;

class Grid 
{
public: 
	class OutOfGridRangeException{};
    void addShip(vector<Coordinates>to_add); //has to be called for each pair of coordinates of a ship
    bool canPlaceShipHere(unsigned int row, unsigned int column); //has to be called for each pair of coordinates that are to be assigned to a ship
    bool canFireHere(unsigned int row, unsigned int column, int size, vector<Coordinates>::iterator coordinates);
	void fire(unsigned int row, unsigned int column); 
	bool isSunkHere(unsigned int row, unsigned int column); //has to be called for each pair of coordinates
	bool isNotShotYetHere(unsigned int row, unsigned int column);
	bool isShipHere(unsigned int row, unsigned int column);
private: 
    GridField fields[ROWS][COLUMNS];
};

#endif //_GRID_H