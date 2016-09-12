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
	for (int i = 0; i < axisId.size() ; i++){
		Serial.print("\t nuevo eje con ID:");
		Serial.println(axisId[i]);
	}
		
}

// --------------------     FUNCTIONALITIES      --------------------


void MyArduino::processOrders( vector<Order> orders2Process ){
  int result;
  for(int nOrder=0; nOrder< orders2Process.size(); nOrder++){
    switch( orders2Process[nOrder].recognizeCmdType() ){    
      case Order::CMD_TYPE::AXES:  
        switch(orders2Process[nOrder].who){
			case 0:
				Serial.println("\n Comando procesado por eje 0 ");
				break;
			case 1:
				Serial.println("\n Comando procesado por eje 1 ");
				break;
			case 2:
				Serial.println("\n Comando procesado por eje 2 ");
				break;
			default:
				Serial.print("\n El eje: ");
				Serial.print(orders2Process[nOrder].who);
				Serial.println("\n Ese eje no existe");
				break;
        }
      break;
      case Order::CMD_TYPE::ARD:       
        result = this->processOrder(orders2Process[0]);
        break;
      default:
        Serial.print("Comando no válido");
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
			Serial.println("\n Comando desconocido:");
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




// --------------------    SUPPORT FUNCTIONS     --------------------
// --------------------     PRIVATE METHODS      --------------------