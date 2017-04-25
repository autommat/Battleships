
#ifndef _HUMANUSERINTERFACE_H
#define _HUMANUSERINTERFACE_H
#define SMALLEST_NUMBER_USED_IN_PROGRAM 0
#define BIGGEST_NUMBER_USED_IN_PROGRAM 9
#include <string>
#include <sstream>
using namespace std;

class HumanUserInterface 
{
public: 
	virtual ~HumanUserInterface();
    
    virtual int getCoordinate() = 0;
    
    virtual void displayInfo(stringstream& info) = 0;

	virtual void operator<<(stringstream& str) = 0;
};

#endif //_HUMANUSERINTERFACE_H