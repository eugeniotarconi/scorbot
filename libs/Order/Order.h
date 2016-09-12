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
		enum    CMD_TYPE {AXES=1,ARD,NO_RECONIZED_CMD_TYPE};
		enum    CMD {BREAK=1,LOG_MODE,NO_RECONIZED_CMD};
		enum    ARG_TYPE {ALL=1,NO_RECONIZED_ARGS_TYPE};
		
		string cmdType;
		int    who;
		string cmd;
		string args;		
		
		/** STATUS:V  ||	DEFAULT CONSTRUCTOR */
		Order();
		
		/** STATUS:V  ||	DEFAULT DESTRUCTOR */
		~Order(){};
		
		
		// -------------------- SETTERS GETTERS & PRINTS --------------------
		// --------------------      FUNCTIONALITIES     --------------------
		
		/** STATUS:IC || Recognize is a input string is a valid cmd type 	 
		*
		*  It is useful before set the cmdType variable; verify if it is valid before update or set the instance
		*/
		Order::CMD_TYPE recognizeCmdType(string Word);

		/** STATUS:IC || Pass a self string type to his enum value	 
		*
		*  It is useful to use the instance's variable cmdType inside a switch; pass string to enum
		*/
		Order::CMD_TYPE recognizeCmdType();
		
		/** STATUS:IC || Recognize is a input string is a valid cmd	 
		*
		*  It is useful before set the cmd variable; verify if it is valid before update or set the instance
		*/
		Order::CMD recognizeCmd(string Word);

		/** STATUS:IC || Pass a self string type to his enum value	 
		*
		*  It is useful to use the instance's variable cmd inside a switch; pass string to enum
		*/
		Order::CMD recognizeCmd();
		
		/** STATUS:IC ||	 */
		Order::ARG_TYPE recognizeArgType(string Word);
		
		// --------------------    SUPPORT FUNCTIONS     --------------------
	private:
		// --------------------     PRIVATE METHODS      --------------------
};


#endif
