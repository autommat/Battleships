
#ifndef _CONSOLEINPUT_H
#define _CONSOLEINPUT_H
#include "HumanUserInterface.h"

class ConsoleInput : public HumanUserInterface
{
public: 
	ConsoleInput();
    
    int getCoordinate();
    
	void displayInfo(stringstream& info);

	void operator<<(stringstream& str);
};

#endif //_CONSOLEINPUT_H