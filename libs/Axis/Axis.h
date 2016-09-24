#ifndef Axis_h
#define Axis_h


#include"Arduino.h"

#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>

#include <Order.h>

using namespace std;

class Axis{
	public:
	
		/** STATUS:V  ||	DEFAULT CONSTRUCTOR */
		Axis();	
		
		/** STATUS:V  ||	DEFAULT DESTRUCTOR */
		~Axis(){};
		
		
		
// -------------------- SETTERS GETTERS & PRINTS --------------------


void setId(short newId);

short getId();

void setBrakePin(short newBrakePin);

// --------------------      FUNCTIONALITIES     --------------------


/** STATUS:IC */
int processOrder(Order newOrder);


void brake(Order::ARG brakeMode);

// --------------------    SUPPORT FUNCTIONS     --------------------
	private:
		short id;
		short brakePin;
		
// --------------------     PRIVATE METHODS      --------------------
bool str2Int(string toConvert,int &converted);
};
#endif
