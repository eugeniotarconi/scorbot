/** 
* 
*  
*/

#include "Axis.h"


Axis::Axis(MySerial *newMySerial){
	this->id = -1;
	this->brakePin = -1;
	this->mySerial = newMySerial;
}

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

int Axis::processOrder(Order newOrder){
	
	int resultOfProcessedOrder = -1; // error by default

	this->mySerial->debug(CR"Here Axis: %d | Doing CMD: "CR,this->id,newOrder.cmd.c_str());
	
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
			this->mySerial->error("\n AXIS: Comando desconocido:");			
			resultOfProcessedOrder = -1;
			break;
	}
	return resultOfProcessedOrder;
}

void Axis::brake(Order::ARG brakeMode){
	
	if(brakeMode == Order::ARG::ON){
		digitalWrite(this->brakePin,HIGH);
		this->mySerial->debug(CR"Here Axis[%d]: brake ON "CR,this->id);
	}else{		
		digitalWrite(this->brakePin,LOW);
		this->mySerial->debug(CR"Here Axis[%d]: brake OFF "CR,this->id);
	}
}

bool Axis::str2Int(string toConvert,int &converted){
	
	bool areValid = false;
	char *end;	
	converted  = strtol(toConvert.c_str(),&end,10);
	if (!*end){
		areValid = true;
	}
	else{
		return areValid = false;
	}		
	
	return areValid;
}