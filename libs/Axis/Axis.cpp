/** 
* 
*  
*/

#include "Axis.h"

/** DEFAULT CONSTRUCTOR */
Axis::Axis(){
	this->id = -1;
	this->brakePin = -1;
}


// -------------------- SETTERS GETTERS & PRINTS --------------------


void Axis::setId(short newId){
	this->id = newId;
}

short Axis::getId(){
	return this->id;
}

void Axis::setBrakePin(short newBrakePin){
	this->brakePin = newBrakePin;
	pinMode(this->brakePin, OUTPUT);
	
}


// --------------------      FUNCTIONALITIES     --------------------


/**	DEFAULT CONSTRUCTOR */
int Axis::processOrder(Order newOrder){
	
	int resultOfProcessedOrder = -1; // error by default

	Serial.print("\n  Here Axis 1:");
	Serial.println(this->id);
	Serial.print("Doing Cmd:");
	Serial.println(newOrder.cmd.c_str());
	
	switch(newOrder.recognizeCmd()){
		case Order::CMD::BRAKE:
			brake(newOrder.recognizeArg());
			resultOfProcessedOrder = 1;
			break;	
		case Order::CMD::SET_BRAKE_PIN:
			int Pin;
			Pin=13;
			str2Int(newOrder.args,Pin);
			setBrakePin(Pin);
			resultOfProcessedOrder = 1;
			break;			
		default:		
			Serial.println("\n AXIS: Comando desconocido:");			
			resultOfProcessedOrder = -1;
			break;
	}
	return resultOfProcessedOrder;
}

void Axis::brake(Order::ARG brakeMode){
	
	if(brakeMode == Order::ARG::ON){
		digitalWrite(this->brakePin,HIGH);
		Serial.print("encendido");
	}else{
		Serial.print("apagado");
		digitalWrite(this->brakePin,LOW);
	}
}


// --------------------    SUPPORT FUNCTIONS     --------------------
// --------------------     PRIVATE METHODS      --------------------

bool Axis::str2Int(string toConvert,int &converted){
	
	bool areValid = false;
	char *end;	
	converted  = strtol(toConvert.c_str(),&end,10);
	if (!*end){
		//Serial.print("\n SI:");
		//Serial.println(whosInt[nOrder]);
		areValid = true;
	}
	else{
		//Serial.print("\n NO:");
		//Serial.println(end);
		return areValid = false;
	}		
	
	return areValid;
}