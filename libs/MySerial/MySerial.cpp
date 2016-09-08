/** 
* 
*  
*/

#include "MySerial.h"


/** Default constructor*/
MySerial::MySerial(long newSerialBaud, char newToken, short newMAX_ARGS){	

// Sentence variables	
	inputSentence       = "";        // a string to hold incoming data
	sentenceIsComplete  = false;   // whether the string is complete
	separatorToken      = newToken;       // token for separate arguments
	endOfSentence 		= '\n';
	//vector<string> sentenceComponents; 
// orders variables
	//vector<Order>  orders;
	fetchOrderTurn 		= 0;
// Serial communication variables	
    serialBaud          = newSerialBaud;  
	SERIAL_BUFFER_SIZE  = 63;
	MAX_ARGS            = newMAX_ARGS; 	
	
	// pasar esta acción al método init()
	Serial.begin(serialBaud);		
}

/** return the sentence components*/
vector<string>  MySerial::getSentenceComponents(){
	return this->sentenceComponents;
}

/** return the sentence components*/
string MySerial::getInputSentence(){
	return this->inputSentence;
};

/** parse the input sentence in components
* 
*  Devuelve el numero de componentes que tiene la Sentencia
*
*  Mejoras propuestas:
*---
*  Hay que ponerlo a prueba de sentencias con varios espacios en blanco seguidos
*  O sentencias que sean enteras en blanco
*  hay que decidir si se excede el numero de componenetes permitidos que ocurre con los
*  componentes que se habían conseguido, si se borran o se quedan
*/
int MySerial::parseSentence(){
	// count if the string is bigger than MAX_ARGS
	int numberOfSentenceComponents = 0; 
	string sentenceComponent;
	stringstream ssInputSentence(this->inputSentence);		
	while(getline(ssInputSentence,sentenceComponent,separatorToken) && sentenceComponent.size() > 0){
		sentenceComponents.push_back(sentenceComponent);
		numberOfSentenceComponents++;
		if(numberOfSentenceComponents>(this->MAX_ARGS -1) ){
			return -1;
		}
	}      
	
	return numberOfSentenceComponents;
};

/** parse the input sentence in orders
* 
*  
*/
int MySerial::parseSentenceByOrders(){
	// count if the string is bigger than MAX_ARGS
	int numberOfOrders = 0; 
	// Deberá utilizar parseSentence y filtrar todos los components para crear las ordenes	
	return numberOfOrders;
};

/** mySerialEvent 
* esta función está pendiente de los eventos en el puerto serie
* si el caracter que llega no es  \n añade a inputString y lo considera
* una misma entidad
*/
bool MySerial::mySerialEvent(){
	
	bool serialError = false;
	if(Serial.available()>=this->SERIAL_BUFFER_SIZE){
	    serialError = true;
	}
	while (Serial.available()) {		
		char inChar = (char)Serial.read();
		if (inChar == endOfSentence){				
            sentenceIsComplete = true;
		}
		else{
		    inputSentence += toupper(inChar); 
		}   		
	}		
	return serialError;
}

/** Get true if Sentence is Complete
* 
*  Devuelve un booleano de si es verdadero que la cadena por puerto serie está completa
*/
bool MySerial::sentenceComplete(){
	return sentenceIsComplete;
}

/** reset the Myserial status to get another sentence
* 
*  Devuelve un booleano de si es verdadero que la cadena por puerto serie está completa
*/
void MySerial::flushSentence(){
// Sentence variables
	//this->inputSentence.clear();
	inputSentence       = "";      		// Comprove if it is necesary
	sentenceIsComplete  = false;   		// whether the string is complete
	//separatorToken      = newToken;   // token for separate arguments
	//endOfSentence 		= '\n';
	sentenceComponents.clear();
	//vector<string> sentenceComponents; 
// orders variables
	//vector<Order>  orders;
	fetchOrderTurn 		= 0;		
// Serial communication variables
}