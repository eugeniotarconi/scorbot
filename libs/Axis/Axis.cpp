/** 
* 
*  
*/

#include "Axis.h"

/** DEFAULT CONSTRUCTOR */
Axis::Axis(){
	
}


// -------------------- SETTERS GETTERS & PRINTS --------------------
// --------------------      FUNCTIONALITIES     --------------------


/**	DEFAULT CONSTRUCTOR */
int Axis::processOrder(Order newOrder){
	
	int resultOfProcessedOrder = -1; // error by default
	
	Serial.print("\n Eje- mi cmd es:");
	Serial.println(newOrder.cmd.c_str());
	
	switch(newOrder.recognizeCmd()){
		case Order::CMD::BREAK:
			resultOfProcessedOrder = 1;
			break;		
		default:
			Serial.println("\n Comando desconocido:");
			resultOfProcessedOrder = -1;
			break;
	}
	Serial.println(resultOfProcessedOrder);
	return resultOfProcessedOrder;
}


// --------------------    SUPPORT FUNCTIONS     --------------------
// --------------------     PRIVATE METHODS      --------------------