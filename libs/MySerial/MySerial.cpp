/** 
* 
*  
*/

#include "MySerial.h"

/** isStringComplete
* 
*  Devuelve un booleano de si es verdadero que la cadena por puerto serie está completa
*/
MySerial::MySerial(long newSerialBaud, char newToken, short newMAX_ARGS){	
    // Set the obtained variables
	serialBaud          = newSerialBaud;    
	sentenceIsComplete  = false;
	separatorToken      = newToken;
	MAX_ARGS            = newMAX_ARGS;
	// set default variables
	inputSentence       = "";
	endOfSentence 		= '\n';
	numberOfOrders 		= 0;
	
	// Start the serial process
	Serial.begin(serialBaud);	
}

/** isStringComplete
* 
*  Devuelve un booleano de si es verdadero que la cadena por puerto serie está completa
*/
vector<string>  MySerial::getSentenceComponents(){
	return this->sentenceComponents;
}

/** isStringComplete
* 
*  Devuelve un booleano de si es verdadero que la cadena por puerto serie está completa
*/
int MySerial::parseSentence(){
	// count if the string is bigger than MAX_ARGS
	int numberOfSentenceComponents = 0; 
	string sentenceComponent;
	stringstream ssInputSentence(this->inputSentence);		
	
	while(getline(ssInputSentence,sentenceComponent,separatorToken) && sentenceComponent.size() > 0){
		sentenceComponents.push_back(sentenceComponent);
		numberOfSentenceComponents++;
		if(numberOfSentenceComponents>MAX_ARGS){
			return -1;
		}
	}      
	
	return numberOfSentenceComponents;
};

/** isStringComplete
* 
*  Devuelve un booleano de si es verdadero que la cadena por puerto serie está completa
*/
vector<MySerial::order> MySerial::parseSentenceByOrders(){
	
	return orders;
};

/** mySerialEvent 
* esta función está pendiente de los eventos en el puerto serie
* si el caracter que llega no es  \n añade a inputString y lo considera
* una misma entidad
*/
void MySerial::mySerialEvent(){
	
	while (Serial.available()) {
		// get the new byte:
		char inChar = (char)Serial.read();
		// if the incoming character is a newline, set a flag
		// so the main loop can do something about it:
		if (inChar == endOfSentence)
		  sentenceIsComplete = true;
		else{
		  // add it to the inputString:
		  inputSentence += inChar;	  
		}      
  }
  
  //inputString.toUpperCase();
}

/** isStringComplete
* 
*  Devuelve un booleano de si es verdadero que la cadena por puerto serie está completa
*/
bool MySerial::sentenceComplete(){
	return sentenceIsComplete;
}

/** isStringComplete
* 
*  Devuelve un booleano de si es verdadero que la cadena por puerto serie está completa
*/
void MySerial::flushSentence(){
	this->inputSentence.clear();
	sentenceIsComplete = false;
	sentenceComponents.clear();
}