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
			
}

/** Default constructor*/
void MySerial::init(){
	Serial.begin(this->serialBaud);
}


// -------------------- SETTERS GETTERS & PRINTS --------------------


/** return the sentence components*/
vector<string>  MySerial::getSentenceComponents(){
	return this->sentenceComponents;
}

/** return the sentence components*/
string MySerial::getInputSentence(){
	return this->inputSentence;
};

/** Get true if Sentence is Complete
* 
*  Devuelve un booleano de si es verdadero que la cadena por puerto serie está completa
*/
bool MySerial::sentenceComplete(){
	return sentenceIsComplete;
}

/** Print sentence Components*/
void MySerial::printSentenceComponents(){
	Serial.print("\n\n Number of components:");
	Serial.println(this->sentenceComponents.size());
	for (int i=0; i<this->sentenceComponents.size();i++){
		Serial.print("Component [");
		Serial.print(i);
		Serial.print("]:");
		Serial.println(this->sentenceComponents[i].c_str());
		Serial.print("\n");
	}
  
}

/** Print sentence Components*/
void MySerial::printSentenceOrders(){
	Serial.print("\n\n Number of orders:");
	Serial.println(this->orders.size());
	for (int i=0; i<this->orders.size();i++){
		Serial.print("order [");
		Serial.print(i);
		Serial.println("]:");
		Serial.print("cmd Type:");
		Serial.println(this->orders[i].cmdType.c_str());
		Serial.print("cmd:");
		Serial.println(this->orders[i].cmd.c_str());
		Serial.print("who:");
		Serial.println(this->orders[i].who);
		Serial.print("args:");
		Serial.println(this->orders[i].args.c_str());
		Serial.print("\n");
	}
  
}

/** parse an return the sentence's orders*/
vector<Order> MySerial::getOrders(){
	this->parseSentenceByOrders();
	
	return this->orders;
}


// --------------------      FUNCTIONALITIES     --------------------


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
int MySerial::parseSentenceByComponents(){
	int numberOfSentenceComponents = parseTool(this->inputSentence,this->separatorToken,this->sentenceComponents);
	if(numberOfSentenceComponents>(this->MAX_ARGS -1) ){
			return -1;
	}
	else{
		return numberOfSentenceComponents;
	}
};

/** parse the input sentence in orders
* 
*  
*/
int MySerial::parseSentenceByOrders(){
	
	int toReturn;
	string cmdType;
	vector<string> whos;
	string cmd;
	vector<string> args;	
	
	// se divide la Sentence por components
	parseSentenceByComponents();
	
	// primero se coge el tipo de comando
	cmdType = sentenceComponents[0];
	
	// Segundo se coge el comando (Depurar cmd no es necesario). La clase axis sabrá si es correcto	
	cmd = sentenceComponents[1];
	
	// Depurar los demás sentenceComponents... 	
	for (int i=2; i<sentenceComponents.size();i++){
		// si el comando es de clase axes el primer args son los whos
		if(!strcmp(cmdType.c_str(),"AXES") && i == 2){ 
			// Depurar sentenceComponents[2] if == all --> 
			if(!strcmp(sentenceComponents[i].c_str(),"ALL")){		
				sentenceComponents[i] = "0,1,2,3,4,5";
			};
			// TODO: habría que verificar que son números
			parseTool(sentenceComponents[i],',',whos);
		}else{
			args.push_back(sentenceComponents[i]);
		}					
	}	
	
	toReturn = this->fillOrders(cmdType,cmd,whos,args);

	return toReturn;
};

/** mySerialEvent 
* esta función está pendiente de los eventos en el puerto serie
* si el caracter que llega no es  \n añade a inputString y lo considera
* una misma entidad
*/
bool MySerial::mySerialEvent(){
	
	//Serial.print("evento. Numero de caracteres = ");
	//Serial.println(Serial.available());
	
	bool serialError = false;
	if(Serial.available()>=this->SERIAL_BUFFER_SIZE){
	    serialError = true;
	}
	while (Serial.available()) {		
		char inChar = (char)Serial.read();
		if (inChar == '\n'){				
            sentenceIsComplete = true;
			//Serial.println("\n Sentencia completa por NUEVA LINEA(\ N) ");
		}
		else{
		    inputSentence += toupper(inChar); 
			//Serial.print("\n car:");
			//Serial.println(inChar);
		}   		
	}	
	//Serial.print("\n Sentencia final:");
	//Serial.println(inputSentence.c_str());	
	return serialError;
}

/** reset the Myserial status to get another sentence
* 
*  Devuelve un booleano de si es verdadero que la cadena por puerto serie está completa
*/
void MySerial::flush(){
// Sentence variables
	//this->inputSentence.clear();
	inputSentence       = "";      		// Comprove if it is necesary
	sentenceIsComplete  = false;   		// whether the string is complete
	//separatorToken      = newToken;   // token for separate arguments
	//endOfSentence 		= '\n';
	sentenceComponents.clear();
	//vector<string> sentenceComponents; 
// orders variables
	orders.clear();
	fetchOrderTurn 		= 0;		
// Serial communication variables
}


// --------------------    SUPPORT FUNCTIONS     --------------------


int MySerial::parseTool(string stringToParse, char token, vector<string> &stringParsed){
	int numberOfParts = 0; 
	string part;
	stringstream ssStringToParse(stringToParse);		
	while(getline(ssStringToParse,part,token) && part.size() > 0){
		stringParsed.push_back(part);
		numberOfParts++;		
	}   
	return numberOfParts;
}



// --------------------     PRIVATE METHODS      --------------------


int MySerial::fillOrders(string cmdType, string cmd, vector<string> whos, vector<string> args){
	int toReturn = -1;
	Order newOrder = Order();
	switch( newOrder.recognizeCmdType(cmdType) ){		
		case Order::CMD_TYPE::AXES:
			// Verificar si hay el mismo numero args que de whos?
			if(whos.size() == args.size()){
				// Se rellena la variable orders de la clase.
				
				for(int nOrder; nOrder<whos.size();nOrder++){
					newOrder.cmdType = cmdType;
					newOrder.cmd = cmd;
					newOrder.who = atoi(whos[nOrder].c_str());					
					newOrder.args = args[nOrder];
					this->orders.push_back(newOrder);	
				}	
				toReturn = whos.size();
			}else{
				Serial.println("\n Missing arguments ");
				toReturn = -1;
			}	
		break;
		case Order::CMD_TYPE::ARD:
			newOrder.cmdType = cmdType;
			newOrder.cmd = cmd;
			newOrder.who = -1;					
			newOrder.args = args[0];
			this->orders.push_back(newOrder);
			toReturn = orders.size();
		break;
		default:
			Serial.print("cmdType default fail");
			toReturn = -1;
		break;
	}		
	return toReturn;
}






