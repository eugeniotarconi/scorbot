/** 
* 
*  
*/

#include "MyArduino.h"

MyArduino::MyArduino(MySerial *newMySerial,bool newMasterFlag){
	masterFlag = newMasterFlag;
	this->mySerial = newMySerial;
}

MyArduino::MyArduino( vector<int> axisId ,bool newMasterFlag ){
	
}

// -------------------- SETTERS GETTERS & PRINTS --------------------

void MyArduino::setAxes( vector<int> axisId ){
	Serial.print("Este arduino ha sido creado con los ejes:\n");
	Axis newAxis = Axis();
	for (int i = 0; i < axisId.size() ; i++){
		Serial.print("\t nuevo eje con ID:");
		Serial.println(axisId[i]);
		newAxis.setId(axisId[i]);
		this->axes.push_back(newAxis);
	}
		
}

bool MyArduino::getMasterFlag(){
	return this->masterFlag;
}

// --------------------     FUNCTIONALITIES      --------------------

void MyArduino::serialCommunications(){
	if(this->masterFlag){
		// check the serial port and process
		if(this->mySerial->getSentenceCompleteFlag()){            
			this->orders = this->mySerial->getOrders();    
			this->mySerial->logSentenceOrders();  
			this->mySerial->flush();
		};
	};  
}

void MyArduino::sendOrders2Slaves(){
	this->mySerial->debug(CR"Master Say: i am sending orders to my slaves"CR);
}

void MyArduino::I2CCommunications(){
	this->mySerial->debug(CR"Master Say: checking I2C recieved communications"CR);
}

void MyArduino::processOrders(){
  int result;
  for(int nOrder=0; nOrder< this->orders.size(); nOrder++){
    switch( this->orders[nOrder].recognizeCmdType() ){    
      case Order::CMD_TYPE::AXES:  
		this->mySerial->debug("\n MyArduino said: i am proccesing a axes cmd \n ");
		if(this->checkIfAxisIsMine(this->orders[nOrder].who)){
			axes[this->orders[nOrder].who].processOrder(this->orders[nOrder]);
		}else{
			this->mySerial->debug("that Axis doesnt belong to me; filterMyOrders is neccesary");
		}		
		break;
      case Order::CMD_TYPE::ARD:       
        result = this->processOrder(this->orders[0]);
		this->mySerial->debug("\n MyArduino said: i am proccesing a ard cmd \n ");
        break;
      default:
        this->mySerial->error("\n MyArduino said: Cmd Type no válido\n");
        break;
    }  
  }
  // TODO: habría que hacer un flush con más cuidado
  this->orders.clear();

}

int MyArduino::processOrder(Order newOrder){
	int resultOfProcessedOrder = -1; // error by default
	this->mySerial->debug("\n MyArduino said: mi cmd es:%s \n",newOrder.cmd.c_str());
	switch(newOrder.recognizeCmd()){
		case Order::CMD::LOG_MODE:
			this->mySerial->setLogMode(newOrder.vectorArgs[0],newOrder.vectorArgs[1]);
			break;		
		default:
			this->mySerial->debug("\n MyArduino: Comando Arduino desconocido \n");
			resultOfProcessedOrder = -1;
			break;
	}
	return resultOfProcessedOrder;
}

void MyArduino::readStateMachine(){
	Serial.println("\n Machine Pin state read");
}

void MyArduino::updateStateMachine(){
	Serial.println("\n Machine Pin state update");
}

void MyArduino::filterMyOrders(){ 
	
	this->mySerial->debug(CR"Master Say: i am filtering my orders"CR);
	
}

bool MyArduino::checkIfAxisIsMine(int who){
	bool isMine = false;
	for (int i = 0; i < axes.size() ; i++){
		if(who == axes[i].getId()) 
			isMine = true;
	}
	return isMine;
}





