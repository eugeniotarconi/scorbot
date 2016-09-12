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
// --------------------      FUNCTIONALITIES     --------------------


/** STATUS:IC */
int processOrder(Order newOrder);


// --------------------    SUPPORT FUNCTIONS     --------------------
	private:
// --------------------     PRIVATE METHODS      --------------------

};
#endif
