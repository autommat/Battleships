
#include "Coordinates.h"



Coordinates::Coordinates(unsigned int row,unsigned int column) : row(row), column(column)
{
}

unsigned int Coordinates::getRow() 
{
    return row;
}

unsigned int Coordinates::getColumn() 
{
    return column;
}