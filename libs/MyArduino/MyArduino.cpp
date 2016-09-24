/** 
* 
*  
*/

#include "MyArduino.h"

/** DEFAULT CONSTRUCTOR */
MyArduino::MyArduino(){
	
}

/** CONSTRUCTOR WITH AXES */
MyArduino::MyArduino( vector<int> axisId ){
	
}


// -------------------- SETTERS GETTERS & PRINTS --------------------


/** CONSTRUCTOR WITH AXES */
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


// --------------------     FUNCTIONALITIES      --------------------


void MyArduino::processOrders( vector<Order> orders2Process ){
  int result;
  for(int nOrder=0; nOrder< orders2Process.size(); nOrder++){
    switch( orders2Process[nOrder].recognizeCmdType() ){    
      case Order::CMD_TYPE::AXES:  
		if(this->checkIfAxisIsMine(orders2Process[nOrder].who)){
			axes[orders2Process[nOrder].who].processOrder(orders2Process[nOrder]);
		}else{
			Serial.println("that Axis doesnt belong to me; filterMyOrders is neccesary");
		}		
		break;
      case Order::CMD_TYPE::ARD:       
        result = this->processOrder(orders2Process[0]);
        break;
      default:
        Serial.print("Cmd Type no válido");
        break;
    }  
  }
}


int MyArduino::processOrder(Order newOrder){
	int resultOfProcessedOrder = -1; // error by default
	Serial.print("\n Arduino- mi cmd es:");
	Serial.println(newOrder.cmd.c_str());
	
	switch(newOrder.recognizeCmd()){
		case Order::CMD::LOG_MODE:
			resultOfProcessedOrder = 1;
			break;		
		default:
			Serial.println("\n MyArduino: Comando Arduino desconocido:");
			resultOfProcessedOrder = -1;
			break;
	}
	Serial.println(resultOfProcessedOrder);
	return resultOfProcessedOrder;
}


void MyArduino::readStateMachine(){
	Serial.println("\n Machine Pin state read");
}


void MyArduino::updateStateMachine(){
	Serial.println("\n Machine Pin state update");
}


vector<Order> MyArduino::filterMyOrders(vector<Order> &orders){ 
	vector<Order> ordersFiltered;
	// devuelve un vector de ordenes con los whos que no sean suyos
	// actualiza las ordenes dadas eliminando las que no son suyas
	ordersFiltered = orders;
	
	return ordersFiltered;
}


bool MyArduino::checkIfAxisIsMine(int who){
	bool isMine = false;
	for (int i = 0; i < axes.size() ; i++){
		if(who == axes[i].getId()) 
			isMine = true;
	}
	return isMine;
}


// --------------------    SUPPORT FUNCTIONS     --------------------
// --------------------     PRIVATE METHODS      --------------------

