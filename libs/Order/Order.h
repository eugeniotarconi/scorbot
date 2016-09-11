#ifndef Order_h
#define Order_h
#include"Arduino.h"

#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

class Order{	
	public:
		string cmdType;
		int    who;
		string cmd;
		string args;		
		enum    CMD_TYPE {AXES=1,ARD,NO_RECONIZED_CMD_TYPE};
		enum    ARG_TYPE {ALL=1,NO_RECONIZED_ARGS_TYPE};
		
		/** STATUS:V  ||	DEFAULT CONSTRUCTOR */
		Order();
		
		/** STATUS:V  ||	DEFAULT DESTRUCTOR */
		~Order(){};
		
		
		// -------------------- SETTERS GETTERS & PRINTS --------------------
		
		
		// --------------------      FUNCTIONALITIES     --------------------
		
		/** STATUS:IC ||	 */
		Order::CMD_TYPE recognizeCmdType(string Word);
		
		/** STATUS:IC ||	 */
		Order::ARG_TYPE recognizeArgType(string Word);
		
		
		// --------------------    SUPPORT FUNCTIONS     --------------------
		
		
	private:
		
		
		// --------------------     PRIVATE METHODS      --------------------
};


#endif
