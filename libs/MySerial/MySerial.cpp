/** 
* 
*  
*/

#include "MySerial.h"

MySerial::MySerial(){}

MySerial::MySerial(long newSerialBaud, char newSeparaToken,Order newOrder, string newLogMode){	
	// Sentence variables	
		inputSentence       = "";        
		sentenceCompleteFlag  = false;   
		separatorToken      = newSeparaToken;       
		endOfSentence 		= '\n';
		//vector<string> sentenceComponents; 
	// orders variables
		order = newOrder;
	// Serial communication variables	
		serialBaud          = newSerialBaud;  
		SERIAL_BUFFER_SIZE  = 63;
		setLogMode(this->order.recognizeArg(newLogMode),Order::ARG::ON);
}

void MySerial::init(){	 
    Serial.begin(this->serialBaud);
	while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
	}
}

void MySerial::init(long newSerialBaud){	
	serialBaud = newSerialBaud;
    Serial.begin(this->serialBaud);
}


// --------------------      SETS      --------------------

void MySerial::setLogMode(Order::ARG newLogMode, Order::ARG newStatus){
	this->debug(CR"MySerial said: Mode to change:%d | new Status: %d "CR,newLogMode,newStatus);
	int arrayPositionOfThisMode = getArrayPositionOfThisMode(newLogMode);
	if(newStatus == Order::ARG::ON){
		this->logMode[arrayPositionOfThisMode] = true;
	}else{
		this->logMode[arrayPositionOfThisMode] = false;
	}
		
}

// --------------------      GETS      --------------------

int MySerial::getArrayPositionOfThisMode(Order::ARG mode){
	int arrayPositionOfThisMode;
	switch(mode){
		case Order::ARG::NO_OUTPUT:
			arrayPositionOfThisMode = 0;
			break;	
		case Order::ARG::ERROR:	
			arrayPositionOfThisMode = 1;		
			break;	
		case Order::ARG::INFO:	
			arrayPositionOfThisMode = 2;		
			break;	
		case Order::ARG::DEBUG:		
			arrayPositionOfThisMode = 3;		
					break;	
		case Order::ARG::VERBOSE:	
			arrayPositionOfThisMode = 4;		
					break;					
		default:			
			this->error("\n MySerial said: setLogMode ARG newStatus unknown\n");
		break;
	}
	return arrayPositionOfThisMode;
}

vector<string>  MySerial::getSentenceComponents(){
	return this->sentenceComponents;
}

string MySerial::getInputSentence(){
	return this->inputSentence;
};

bool MySerial::getSentenceCompleteFlag(){
	return sentenceCompleteFlag;
}

vector<Order> MySerial::getOrders(){
	// esto no debe ir aquí: debería haber un método que sea procces sentence
	this->parseSentenceByOrders();
	
	return this->orders;
}

// --------------------      LOGS      --------------------

void MySerial::logSentenceComponents(){
	info("\n\n MySerial said:  Number of components:%d \n",this->sentenceComponents.size());
	for (int i=0; i<this->sentenceComponents.size();i++){
		info("Component [%d]: %s "CR,i,this->sentenceComponents[i].c_str());
	}
  
}

void MySerial::logSentenceOrders(){
	info("\n\n Number of orders:%d",this->orders.size());
	for (int i=0; i<this->orders.size();i++){
		debug("\n order [%d]:"CR,i);
		debug("\t cmd Type: %s"CR,this->orders[i].cmdType.c_str());		
		debug("\t cmd: %s"CR,this->orders[i].cmd.c_str());
		debug("\t who: %d"CR,this->orders[i].who);		
		debug("\t args: %s "CR,this->orders[i].args.c_str());
		for (int j=0; j<this->orders[i].vectorArgs.size();j++){
			debug("\t arg[%d]: %d \n"CR,j,orders[i].vectorArgs[j]);
		}
	}  
}

void MySerial::error(const char* msg, ...){
    if (shouldPrint(Order::ARG::ERROR)) {   
		print ("\nERROR: ",0);
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}

void MySerial::info(const char* msg, ...){
    if (shouldPrint(Order::ARG::INFO)) {
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}

void MySerial::debug(const char* msg, ...){
    if (shouldPrint(Order::ARG::DEBUG)) {
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}

void MySerial::verbose(const char* msg, ...){
    if (shouldPrint(Order::ARG::VERBOSE)) {
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}

// --------------------      FUNCTIONALITIES     --------------------


int MySerial::parseSentenceByComponents(){
	int numberOfSentenceComponents = parseTool(this->inputSentence,this->separatorToken,this->sentenceComponents);
	return numberOfSentenceComponents;
};

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
			this->parseTool(sentenceComponents[i],',',whos);
		}else{
			args.push_back(sentenceComponents[i]);
		}					
	}	
	
	toReturn = this->fillOrders(cmdType,cmd,whos,args);

	return toReturn;
};

bool MySerial::mySerialEvent(){
	debug(CR"-----------------------------------------------------------"CR);
	debug(CR"MySerial said: New Serial Event, Number of bytes = %d"CR,Serial.available());
	
	bool serialError = false;
	if(Serial.available()>=this->SERIAL_BUFFER_SIZE){
	    serialError = true;
	}
	while (Serial.available()) {		
		char inChar = (char)Serial.read();
		if (inChar == '\n'){				
            sentenceCompleteFlag = true;
			debug("\n MySerial said: Sentence complete (end by \ N) ");
		}
		else{
		    inputSentence += toupper(inChar); 
			//debug("\n MySerial said: char: %c",inChar);
		}   		
	}	
	debug("\n MySerial said: Final Sentence: %s",inputSentence.c_str());
	return serialError;
}

void MySerial::flush(){
// Sentence variables
	//this->inputSentence.clear();
	inputSentence       = "";      		// Comprove if it is necesary
	sentenceCompleteFlag  = false;   		// whether the string is complete
	//separatorToken      = newToken;   // token for separate arguments
	//endOfSentence 		= '\n';
	sentenceComponents.clear();
	//vector<string> sentenceComponents; 
    order.clear();
	orders.clear();	
// Serial communication variables
}

// --------------------     PRIVATE METHODS      --------------------

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

int MySerial::fillOrders(string cmdType, string cmd, vector<string> whos, vector<string> args){
	int toReturn = -1;
	vector<int> whosInt;	
	vector<string> parsedArgs;
	
	switch( this->order.recognizeCmdType(cmdType) ){		
		case Order::CMD_TYPE::AXES:		
			// verificar que los whos son numeros validos
			if(!this->verifyWhos(whos,whosInt)){
				error("\n MySerial said: Some who param is not a number or not valid");
				return toReturn;
			};
			// Verificar si hay el mismo numero args que de whos?
			if(whos.size() != args.size()){		
				error("\n MySerial said: Missing arguments in axes command: less args than axes ");
				return toReturn;
			};
			// Se rellena la variable orders de la clase.				
			for(int nOrder; nOrder<whos.size();nOrder++){
				this->order.cmdType = cmdType;
				this->order.cmd = cmd;
				this->order.who = whosInt[nOrder];					
				this->order.args = args[nOrder];
				// fill vector<ARG> vectorArgs in Order
				parseTool(this->order.args,',',parsedArgs);
				this->order.setVectorArgs(parsedArgs);
				
				this->orders.push_back(this->order);	
			}	
			toReturn = whos.size();
		break;
		case Order::CMD_TYPE::ARD:
			this->order.cmdType = cmdType;
			this->order.cmd = cmd;
			this->order.who = -1;					
			this->order.args = args[0];
			// fill vector<ARG> vectorArgs in Order
			parseTool(this->order.args,',',parsedArgs);
			this->order.setVectorArgs(parsedArgs);		
			
			this->orders.push_back(this->order);
			toReturn = orders.size();
		break;
		default:
			error(" MySerial said: cmdType default fail");
			toReturn = -1;
		break;
	}		
		
	return toReturn;
}

bool MySerial::verifyWhos(vector<string> whos,vector<int> &whosInt){
	
	bool areValid = false;
	char *end;
	for(int nOrder=0; nOrder<whos.size();nOrder++){
		whosInt[nOrder]  = strtol(whos[nOrder].c_str(),&end,10);
		if (!*end){
			debug("\n MySerial said: valid who = %d",whosInt[nOrder]);
			areValid = true;
		}
		else{
			debug("\n MySerial said: invalid who = %T",end);
			return areValid = false;
		}		
	}
	return areValid;
}

void MySerial::print(const char *format, va_list args) {
    //
    // loop through format string
    for (; *format != 0; ++format) {
        if (*format == '%') {
            ++format;
            if (*format == '\0') break;
            if (*format == '%') {
                Serial.print(*format);
                continue;
            }
            if( *format == 's' ) {
				register char *s = (char *)va_arg( args, int );
				Serial.print(s);
				continue;
			}
            if( *format == 'd' || *format == 'i') {
				Serial.print(va_arg( args, int ),DEC);
				continue;
			}
            if( *format == 'x' ) {
				Serial.print(va_arg( args, int ),HEX);
				continue;
			}
            if( *format == 'X' ) {
				Serial.print("0x");
				Serial.print(va_arg( args, int ),HEX);
				continue;
			}
            if( *format == 'b' ) {
				Serial.print(va_arg( args, int ),BIN);
				continue;
			}
            if( *format == 'B' ) {
				Serial.print("0b");
				Serial.print(va_arg( args, int ),BIN);
				continue;
			}
            if( *format == 'l' ) {
				Serial.print(va_arg( args, long ),DEC);
				continue;
			}

            if( *format == 'c' ) {
				Serial.print(va_arg( args, int ));
				continue;
			}
            if( *format == 't' ) {
				if (va_arg( args, int ) == 1) {
					Serial.print("T");
				}
				else {
					Serial.print("F");				
				}
				continue;
			}
            if( *format == 'T' ) {
				if (va_arg( args, int ) == 1) {
					Serial.print("true");
				}
				else {
					Serial.print("false");				
				}
				continue;
			}

        }
        Serial.print(*format);
    }
 }
  
bool MySerial::shouldPrint(Order::ARG mode){
	bool result = false;
	int indexMode = getArrayPositionOfThisMode(mode);
	if(logMode[indexMode]) result = true;
	return result;
}



