
#ifndef _COORDINATES_H
#define _COORDINATES_H

class Coordinates 
{
public: 
    Coordinates(unsigned int row,unsigned int column);
    
    unsigned int getRow();
    unsigned int getColumn();

private: 
    unsigned int row;
    unsigned int column;
};

#endif //_COORDINATES_H